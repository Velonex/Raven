#include "NightFallApplication.h"
#include <NightFall/application/KeyCodes.h>
#include <NightFall/application/Input.h>
#include <NightFall/application/MouseCodes.h>
#include <NightFall/logger/Logger.h>
#include <glad/glad.h>
#include <NightFall/rendering/GraphicsContext.h>
#include <NightFall/rendering/Renderer.h>
#include <imgui.h>

namespace nfe {
	NightFallApplication* NightFallApplication::_app = nullptr;
	bool NightFallApplication::_initialized = false;
	static float* backgroundColor = new float[3];

	int NightFallApplication::init(char* name)
	{
		if (!_initialized) {
			LOG_ENGINE_ERROR("You first have to set the instance!");
			return -1;
		}
		Logger::init(name);
		LOG_ENGINE_TRACE("Initializing...");
		_eventHandler = new EventHandler();
		WindowProps props(1280, 720, name);
		_window = Window::createWindow(props);
		_eventHandler->subscribe(this, EventType::ALL);
		Input::setInstance(Input::createInput());
		_layerStack = new LayerStack();
		_layerStack->pushOverlay(_imGuiLayer = new ImGuiLayer());
		LOG_ENGINE_INFO("Successfully initialized.");

		glGenVertexArrays(1, &_vertexArray);
		glBindVertexArray(_vertexArray);


		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		_vertexBuffer = VertexBuffer::create(vertices, sizeof(vertices));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};
		_vertexBuffer->setLayout(layout);
		unsigned int indices[3] = {
			0, 1, 2
		};

		_indexBuffer = IndexBuffer::create(indices, sizeof(indices));

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				gl_Position = vec4(a_Position, 1.0);
				v_Position = a_Position;
				v_Color = a_Color;
			}
		)";
		std::string pixelSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main() {
				color = v_Color;
			}
		)";
		_shader = new Shader(vertexSrc, pixelSrc);
		backgroundColor[0] = 0.1f;
		backgroundColor[1] = 0.1f;
		backgroundColor[2] = 0.1f;
		return 0;
	}
	void NightFallApplication::run()
	{
		if (!_initialized) {
			ASSERT(false, "You first have to set the instance");
			return;
		}
		while (_running) {
			Renderer::setClearColorRGBA(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glBindVertexArray(_vertexArray);
			_shader->bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			for (auto it = _layerStack->end(); it != _layerStack->begin(); )
			{
				(*--it)->onUpdate();
			}
			
			_imGuiLayer->beginFrame();
			{
				ImGui::Begin("Controls");
				ImGui::Text("Background color:");
				ImGui::SliderFloat3("", backgroundColor, 0.0f, 1.0f, "%.2f");
				ImGui::End();
			}
			for (auto it = _layerStack->end(); it != _layerStack->begin(); )
			{
				(*--it)->onImGuiRender();
			}
			_imGuiLayer->endFrame();
			_window->onUpdate();
			_shader->bind();
		}
	}
	int NightFallApplication::quit()
	{
		if (!_initialized) {
			LOG_ENGINE_ERROR("You first have to set the instance!");
			return -1;
		}
		LOG_ENGINE_TRACE("Stopping...");
		for (auto it = _layerStack->end(); it != _layerStack->begin(); )
		{
			(*--it)->onDetach();
		}
		_layerStack->~LayerStack();
		delete _window;
		delete _eventHandler;
		delete _layerStack;
		delete _shader;
		LOG_ENGINE_INFO("Stopped.");
		return 0;
	}
	void NightFallApplication::onEvent(Event* e)
	{
		//LOG_ENGINE_TRACE("Event received: {}", e->getName());

		switch (e->getType()) {
		case EventType::EVENT_WINDOW_CLOSE:
			_running = false;
		default:
			return;
		}
	}
}