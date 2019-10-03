#include "LibLogger.h"

#ifndef DIST 
namespace nfe {
	
	std::shared_ptr<spdlog::logger> LibLogger::_libLogger;

	void LibLogger::init()
	{
		if (_libLogger) {
			LOG_LIB_ERROR("Already initialized Logger!");
			return;
		}
		spdlog::set_pattern("%^[%T] %n: %v%$");
		_libLogger = spdlog::stdout_color_mt("NightFallLib");
		_libLogger->set_level(spdlog::level::level_enum::trace);
	}

}
#else 
namespace nfe {

	void LibLogger::init(char* name)
	{

	}

}
#endif