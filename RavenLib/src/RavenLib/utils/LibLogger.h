#pragma once
#ifndef DIST
#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
namespace rvn{
	class LibLogger
	{
		static std::shared_ptr<spdlog::logger> _libLogger;
	public:
		static void init();
		inline static std::shared_ptr<spdlog::logger> getLibLogger() { return _libLogger; }
	};
}

#define LOG_LIB_TRACE(...)    ::rvn::LibLogger::getLibLogger()->trace(__VA_ARGS__)
#define LOG_LIB_INFO(...)     ::rvn::LibLogger::getLibLogger()->info(__VA_ARGS__)
#define LOG_LIB_WARN(...)     ::rvn::LibLogger::getLibLogger()->warn(__VA_ARGS__)
#define LOG_LIB_ERROR(...)    ::rvn::LibLogger::getLibLogger()->error(__VA_ARGS__)
#else
namespace rvn {
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