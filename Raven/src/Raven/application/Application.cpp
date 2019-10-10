#include "Application.h"
#include <Raven.h>
#include <GLFW/glfw3.h>
#include <Raven/rendering/Renderer.h>
#include <RavenLib/InitLib.h>

namespace rvn {
	Application* Application::_app = nullptr;
	bool Application::_initialized = false;

	int Application::init(char* name)
	{
		if (!_initialized) {
			LOG_ENGINE_ERROR("You first have to set the instance!");
			return -1;
		}
		Logger::init(name);
		initLib();
		LOG_ENGINE_TRACE("Initializing...");
		_eventHandler = createScope<EventHandler>();
		WindowProps props(1280, 720, name);
		_window.reset(Window::createWindow(props));
		_eventHandler->subscribe(this, EventType::ALL);
		Input::setInstance(Input::createInput());
		_layerStack = createScope<LayerStack>();
		_layerStack->pushOverlay(_imGuiLayer = new ImGuiLayer());
		Renderer::init();
		LOG_ENGINE_INFO("Successfully initialized.");

		return 0;
	}
	void Application::run()
	{
		if (!_initialized) {
			ASSERT(false, "You first have to set the instance");
			return;
		}
		while (_running) {
			float time = (float)glfwGetTime();
			Timestep timestep = time - _lastFrameTime;
			_lastFrameTime = time;

			RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::clear();
			for (auto it = _layerStack->end(); it != _layerStack->begin(); )
			{
				(*--it)->onUpdate(timestep);
			}
			_imGuiLayer->beginFrame();
			{
				ImGui::Begin("Renderer");
				ImGui::Text("FPS: %f", 1 / timestep.getSeconds());
				ImGui::End();
			}
			for (auto it = _layerStack->end(); it != _layerStack->begin(); )
			{
				(*--it)->onImGuiRender();
			}
			_imGuiLayer->endFrame();
			_window->onUpdate();
		}
	}
	int Application::quit()
	{
		if (!_initialized) {
			LOG_ENGINE_ERROR("You first have to set the instance!");
			return -1;
		}
		LOG_ENGINE_TRACE("Stopping...");
		_layerStack->~LayerStack();
		LOG_ENGINE_INFO("Stopped.");
		return 0;
	}
	void Application::onEvent(Event* e)
	{
		for (auto it = _layerStack->end(); it != _layerStack->begin(); )
		{
			(*--it)->onEvent(e);
		}
		switch (e->getType()) {
		case EventType::EVENT_WINDOW_CLOSE:
			_running = false;
			break;
		default:
			return;
		}
	}
}