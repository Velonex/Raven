#include "NightFallApplication.h"
#include <NightFall/application/KeyCodes.h>
#include <NightFall/application/Input.h>
#include <NightFall/application/MouseCodes.h>
#include <NightFall/logger/Logger.h>
#include <glad/glad.h>

namespace nfe {
	NightFallApplication* NightFallApplication::_app = nullptr;
	bool NightFallApplication::_initialized = false;

	int NightFallApplication::init(char* name)
	{
		if (!_initialized) {
			LOG_ENGINE_ERROR("You first have to set the instance!");
		}
		Logger::init(name);
		LOG_ENGINE_TRACE("Initializing...");
		_eventHandler = new EventHandler();
		WindowProps props(1280, 720, name);
		_window = Window::createWindow(props);
		_eventHandler->subscribe(this, EventType::ALL);
		Input::setInstance(Input::createInput());
		LOG_ENGINE_INFO("Successfully initialized.");
		return 0;
	}
	void NightFallApplication::run()
	{
		while (_running) {
			glClearColor(0.447f, 0.043f, 0.043f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			_window->onUpdate();
			//LOG_ENGINE_TRACE("{}", Input::isKeyPressed(KEY_W));
		}
	}
	int NightFallApplication::quit()
	{
		LOG_ENGINE_TRACE("Stopping...");
		delete _window;
		delete _eventHandler;
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