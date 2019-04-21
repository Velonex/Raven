#ifndef ASSERT_H_
#define ASSERT_H_
#include <NightFall/logger/Logger.h>

#ifdef PLATFORM_WINDOWS 
	#ifndef DIST
		#define ASSERT(x, ...)	if(x) {\
									LOG_ENGINE_ERROR("Assertion failed: {}.", __VA_ARGS__);\
									__debugbreak();\
								}
	#else 
		#define ASSERT(x, ...)
	#endif
#else
	#error The Spectral Game-Engine yet only supports Windows!
#endif
#endif