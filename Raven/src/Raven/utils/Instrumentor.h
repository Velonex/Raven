#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <sstream>

namespace rvn {

	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	struct ProfileResult
	{
		std::string name;
		long long start, end;
		std::thread::id threadID;
	};

	struct InstrumentationSession
	{
		std::string name;
	};

	class Instrumentor
	{
	private:
		InstrumentationSession* _currentSession;
		std::ofstream _outputStream;
		std::mutex _mutex;
	public:
		Instrumentor()
			: _currentSession(nullptr)
		{
		}

		void beginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			std::lock_guard lock(_mutex);
			if (_currentSession) {
				if (Logger::getEngineLogger()) {
					LOG_ENGINE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, _currentSession->name);
				}
				internalEndSession();
			}
			_outputStream.open(filepath);
			_currentSession = new InstrumentationSession{ name };
			if (_outputStream.is_open()) {
				_currentSession = new InstrumentationSession({ name });
				writeHeader();
			}
			else {
				if (Logger::getEngineLogger()) {
					LOG_ENGINE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
				}
			}
		}

		void endSession()
		{
			std::lock_guard lock(_mutex);
			internalEndSession();
		}
		void writeProfile(const ProfileResult& result)
		{
			std::stringstream json;

			std::string name = result.name;
			std::replace(name.begin(), name.end(), '"', '\'');

			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.end - result.start) << ',';
			json << "\"name\":\"" << name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.threadID << ",";
			json << "\"ts\":" << result.start;
			json << "}";

			std::lock_guard lock(_mutex);
			if (_currentSession) {
				_outputStream << json.str();
				_outputStream.flush();
			}
		}
		static Instrumentor& get()
		{
			static Instrumentor instance;
			return instance;
		}

	private:
		void writeHeader()
		{
			_outputStream << "{\"otherData\": {},\"traceEvents\":[{}";
			_outputStream.flush();
		}

		void writeFooter()
		{
			_outputStream << "]}";
			_outputStream.flush();
		}
		void internalEndSession() {
			if (_currentSession) {
				writeFooter();
				_outputStream.close();
				delete _currentSession;
				_currentSession = nullptr;
			}
		}
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			: _name(name), _stopped(false)
		{
			_startTimepoint = std::chrono::high_resolution_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!_stopped)
				stop();
		}

		void stop()
		{
			auto _endTimepoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(_startTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(_endTimepoint).time_since_epoch().count();

			std::thread::id threadID = std::this_thread::get_id();
			Instrumentor::get().writeProfile({ _name, start, end, threadID });

			_stopped = true;
		}
	private:
		const char* _name;
		std::chrono::time_point<std::chrono::high_resolution_clock> _startTimepoint;
		bool _stopped;
	};
}
#if defined(DEBUG)
#define RVN_PROFILE 1
#endif
#if RVN_PROFILE
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define RVN_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define RVN_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__FUNCSIG__)
		#define RVN_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define RVN_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define RVN_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define RVN_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define RVN_FUNC_SIG __func__
	#else
		#define RVN_FUNC_SIG "RVN_FUNC_SIG unknown!"
	#endif
	#define RVN_PROFILE_BEGIN_SESSION(name, filepath) rvn::Instrumentor::get().beginSession(name, filepath)
	#define RVN_PROFILE_SCOPE(name) rvn::InstrumentationTimer timer##__LINE__(name);
	#define RVN_PROFILE_FUNCTION() RVN_PROFILE_SCOPE(RVN_FUNC_SIG) 
	#define RVN_PROFILE_END_SESSION() rvn::Instrumentor::get().endSession()
#else
	#define RVN_PROFILE_BEGIN_SESSION(name, filepath)
	#define RVN_PROFILE_FUNCTION()
	#define RVN_PROFILE_SCOPE(name)
	#define RVN_PROFILE_END_SESSION()
#endif