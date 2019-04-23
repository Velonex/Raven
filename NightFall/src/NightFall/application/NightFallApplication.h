#ifndef NIGHTFALLAPPLICATION_H_
#define NIGHTFALLAPPLICATION_H_
#include <NightFall/event/EventHandler.h>
#include <NightFall/application/Window.h>
#include <NightFall/layers/LayerStack.h>

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
		virtual void onEvent(Event* e) override;
	private:
		static NightFallApplication* _app;
		static bool _initialized;
	private:
		EventHandler* _eventHandler;
		Window* _window;
		LayerStack* _layerStack;
		bool _running = true;;
	};
}
#endif