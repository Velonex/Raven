#ifndef NIGHTFALLAPPLICATION_H_
#define NIGHTFALLAPPLICATION_H_
#include <NightFall/event/EventHandler.h>

namespace nfe {
	class NightFallApplication
	{
	public:
		int init(char* name);
		static void setInstance(NightFallApplication* app) {
			_app = app;
			_initialized = true;
		}
		static NightFallApplication* getInstance() { return _app; }
		EventHandler* getHandler() { return _handler; }
	private:
		static NightFallApplication* _app;
		static bool _initialized;
	private:
		EventHandler* _handler;
	};
}
#endif