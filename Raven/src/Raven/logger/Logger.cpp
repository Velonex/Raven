#include <pch.h>
#include "Logger.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <ctime>
#include <chrono>
#include <string>

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
		std::vector<spdlog::sink_ptr> sinks;
		sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		// Generating name for logfile
		std::time_t t = std::time(0);
		std::tm now = *std::localtime(&t);
		std::string filename = "Raven-" + std::to_string(now.tm_mon) + std::to_string(now.tm_mday) + std::to_string(now.tm_year + 1900) + "-" +
			std::to_string(now.tm_hour) + "-" + std::to_string(now.tm_min) + ".log";
		// 
		sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(std::string(filename), false));

		sinks[0]->set_pattern("[%T][%^%l%$] %n: %v");
		sinks[1]->set_pattern("[%T][%l] %n: %v");

		_engineLogger = std::make_shared<spdlog::logger>("Raven", sinks.begin(), sinks.end());
		spdlog::register_logger(_engineLogger);
		_engineLogger->set_level(spdlog::level::trace);
		_engineLogger->flush_on(spdlog::level::trace);
	
		_appLogger = std::make_shared<spdlog::logger>(name, sinks.begin(), sinks.end());
		spdlog::register_logger(_appLogger);
		_appLogger->set_level(spdlog::level::trace);
		_appLogger->flush_on(spdlog::level::trace);
	}

}
#else 
namespace rvn {

	void Logger::init(char* name)
	{

	}

}
#endif