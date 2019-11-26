#pragma once
#ifndef DIST
#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
namespace rvn{
	class Logger
	{
		static std::shared_ptr<spdlog::logger> _engineLogger;
		static std::shared_ptr<spdlog::logger> _appLogger;
	public:
		static void init(char* app);
		inline static std::shared_ptr<spdlog::logger> getEngineLogger() { return _engineLogger; }
		inline static std::shared_ptr<spdlog::logger> getAppLogger() { return _appLogger; }
	};
}

#define LOG_ENGINE_TRACE(...)    ::rvn::Logger::getEngineLogger()->trace(__VA_ARGS__)
#define LOG_ENGINE_INFO(...)     ::rvn::Logger::getEngineLogger()->info(__VA_ARGS__)
#define LOG_ENGINE_WARN(...)     ::rvn::Logger::getEngineLogger()->warn(__VA_ARGS__)
#define LOG_ENGINE_ERROR(...)    ::rvn::Logger::getEngineLogger()->error(__VA_ARGS__)
#define LOG_ENGINE_CRITICAL(...) ::rvn::Logger::getEngineLogger()->critical(__VA_ARGS__)

#define LOG_TRACE(...)	      ::rvn::Logger::getAppLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)	      ::rvn::Logger::getAppLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)	      ::rvn::Logger::getAppLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)	      ::rvn::Logger::getAppLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)     ::rvn::Logger::getAppLogger()->critical(__VA_ARGS__)
#else
namespace rvn {
	class Logger
	{
	public:
		static void init(char* app);
	};
}
#define LOG_ENGINE_TRACE(...)
#define LOG_ENGINE_INFO(...)
#define LOG_ENGINE_WARN(...)
#define LOG_ENGINE_ERROR(...)
#define LOG_ENGINE_CRITICAL(...)

#define LOG_TRACE(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_CRITICAL(...)
#endif