#include "LibLogger.h"

#ifndef DIST 
namespace rvn {
	
	std::shared_ptr<spdlog::logger> LibLogger::_libLogger;

	void LibLogger::init()
	{
		if (_libLogger) {
			LOG_LIB_ERROR("Already initialized Logger!");
			return;
		}
		spdlog::set_pattern("%^[%T] %n: %v%$");
		_libLogger = spdlog::stdout_color_mt("RavenLib");
		_libLogger->set_level(spdlog::level::level_enum::trace);
	}

}
#else 
namespace rvn {

	void LibLogger::init(char* name)
	{

	}

}
#endif