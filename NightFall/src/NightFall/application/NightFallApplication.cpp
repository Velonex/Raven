#include "NightFallApplication.h"
#include <NightFall/logger/Logger.h>

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
		_handler = new EventHandler();
		LOG_ENGINE_INFO("Successfully initialized.");
		return 0;
	}
}