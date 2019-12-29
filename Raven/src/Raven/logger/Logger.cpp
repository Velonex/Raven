#include <pch.h>
#include "Logger.h"

#ifndef DIST 
namespace rvn {
	
	ref<spdlog::logger> Logger::_engineLogger;
	ref<spdlog::logger> Logger::_appLogger;

	void Logger::init(char* name)
	{
		if (_engineLogger) {
			LOG_ENGINE_ERROR("Already initialized Logger!");
			return;
		}
		spdlog::set_pattern("%^[%T] %n: %v%$");
		_engineLogger = spdlog::stdout_color_mt("Raven");
		_engineLogger->set_level(spdlog::level::level_enum::trace);
		_appLogger = spdlog::stdout_color_mt(name);
		_appLogger->set_level(spdlog::level::level_enum::trace);
	}

}
#else 
namespace rvn {

	void Logger::init(char* name)
	{

	}

}
#endif