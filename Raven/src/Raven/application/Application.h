#pragma once
#include <Raven/event/EventHandler.h>
#include <Raven/application/Window.h>
#include <Raven/layers/LayerStack.h>
#include <Raven/layers/layers/ImGuiLayer.h>
#include <Raven/rendering/Shader.h>
#include <Raven/rendering/Buffer.h>
#include <Raven/rendering/VertexArray.h>
#include <Raven/rendering/OrthographicCamera.h>
#include <Raven/core/Timestep.h>
#include <Raven/event/events/WindowEvents.h>

namespace rvn {

	class Application : public EventListener
	{
	public:
		int init(char* name);
		void run();
		int quit();
		static void setInstance(Application* app) {
			_app = app;
			_initialized = true;
		}
		static Application* getInstance() { return _app; }
		EventHandler* getEventHandler() { return _eventHandler.get(); }
		Window* getWindow() { return _window.get(); }
		LayerStack* getLayerStack() { return _layerStack.get(); }
		virtual void onEvent(Event* e) override;
	private:
		void onWindowResize(WindowResizeEvent* e);
	private:
		static Application* _app;
		static bool _initialized;
	private:
		scope<EventHandler> _eventHandler;
		scope<Window> _window;
		ImGuiLayer* _imGuiLayer;
		scope<LayerStack> _layerStack;
		bool _running = true;
		bool _minimized = false;
		float _lastFrameTime = 0.f;
	};
	typedef Application NFApp;
}