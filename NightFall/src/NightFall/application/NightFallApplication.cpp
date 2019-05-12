#include "NightFallApplication.h"
#include <NightFall/application/KeyCodes.h>
#include <NightFall/application/Input.h>
#include <NightFall/application/MouseCodes.h>
#include <NightFall/logger/Logger.h>
#include <glad/glad.h>
#include <NightFall/rendering/GraphicsContext.h>

namespace nfe {
	NightFallApplication* NightFallApplication::_app = nullptr;
	bool NightFallApplication::_initialized = false;

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

		glGenBuffers(1, &_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f,  0.0f,
			 0.5f, -0.5f,  0.0f,
			 0.0f,  0.5f,  0.0f
		};
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

		glGenBuffers(1, &_indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);

		unsigned int indices[3] = {
			0, 1, 2
		};
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		return 0;
	}
	void NightFallApplication::run()
	{
		if (!_initialized) {
			LOG_ENGINE_ERROR("You first have to set the instance!");
			return;
		}
		while (_running) {
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glBindVertexArray(_vertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			for (auto it = _layerStack->end(); it != _layerStack->begin(); )
			{
				(*--it)->onUpdate();
			}
			_imGuiLayer->beginFrame();
			for (auto it = _layerStack->end(); it != _layerStack->begin(); )
			{
				(*--it)->onImGuiRender();
			}
			_imGuiLayer->endFrame();
			_window->onUpdate();

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