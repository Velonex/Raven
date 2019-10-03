#pragma once
#ifndef DIST
#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
namespace nfe{
	class LibLogger
	{
		static std::shared_ptr<spdlog::logger> _libLogger;
	public:
		static void init();
		inline static std::shared_ptr<spdlog::logger> getLibLogger() { return _libLogger; }
	};
}

#define LOG_LIB_TRACE(...)    ::nfe::LibLogger::getLibLogger()->trace(__VA_ARGS__)
#define LOG_LIB_INFO(...)     ::nfe::LibLogger::getLibLogger()->info(__VA_ARGS__)
#define LOG_LIB_WARN(...)     ::nfe::LibLogger::getLibLogger()->warn(__VA_ARGS__)
#define LOG_LIB_ERROR(...)    ::nfe::LibLogger::getLibLogger()->error(__VA_ARGS__)
#else
namespace nfe {
	class LibLogger
	{
	public:
		static void init(char* app);
	};
}
#define LOG_LIB_TRACE(...)
#define LOG_LIB_INFO(...)
#define LOG_LIB_WARN(...)
#define LOG_LIB_ERROR(...)
#endif