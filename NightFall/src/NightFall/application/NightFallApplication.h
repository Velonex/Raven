#pragma once
#include <NightFall/event/EventHandler.h>
#include <NightFall/application/Window.h>
#include <NightFall/layers/LayerStack.h>
#include <NightFall/layers/layers/ImGuiLayer.h>
#include <NightFall/rendering/Shader.h>
#include <NightFall/rendering/Buffer.h>
#include <NightFall/rendering/VertexArray.h>
#include <NightFall/rendering/Camera.h>
#include <NightFall/core/Timestep.h>

namespace nfe {

	class NightFallApplication : public EventListener
	{
	public:
		int init(char* name);
		void run();
		int quit();
		static void setInstance(NightFallApplication* app) {
			_app = app;
			_initialized = true;
		}
		static NightFallApplication* getInstance() { return _app; }
		EventHandler* getEventHandler() { return _eventHandler; }
		Window* getWindow() { return _window; }
		LayerStack* getLayerStack() { return _layerStack; }
		virtual void onEvent(Event* e) override;
	private:
		static NightFallApplication* _app;
		static bool _initialized;
	private:
		EventHandler* _eventHandler;
		Window* _window;
		ImGuiLayer* _imGuiLayer;
		LayerStack* _layerStack;
		bool _running = true;
		float _lastFrameTime = 0.f;
	};
	typedef NightFallApplication NFApp;
}