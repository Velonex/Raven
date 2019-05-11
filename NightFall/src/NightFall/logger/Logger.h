#ifndef _LOGGER_H_
#define _LOGGER_H_
#ifndef DIST
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>
namespace nfe{
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

#define LOG_ENGINE_TRACE(...)    ::nfe::Logger::getEngineLogger()->trace(__VA_ARGS__)
#define LOG_ENGINE_INFO(...)     ::nfe::Logger::getEngineLogger()->info(__VA_ARGS__)
#define LOG_ENGINE_WARN(...)     ::nfe::Logger::getEngineLogger()->warn(__VA_ARGS__)
#define LOG_ENGINE_ERROR(...)    ::nfe::Logger::getEngineLogger()->error(__VA_ARGS__)

#define LOG_TRACE(...)	      ::nfe::Logger::getAppLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)	      ::nfe::Logger::getAppLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)	      ::nfe::Logger::getAppLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)	      ::nfe::Logger::getAppLogger()->error(__VA_ARGS__)
#else
namespace nfe {
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

#define LOG_TRACE(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#endif
#endif