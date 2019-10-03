#pragma once
#include "LibLogger.h"

#ifdef PLATFORM_WINDOWS 
	#ifndef DIST
		#define LIB_ASSERT(x, ...)	if(!(x)) {\
									LOG_LIB_ERROR("Assertion failed: {}.", __VA_ARGS__);\
									__debugbreak();\
								}
	#else
		#define LIB_ASSERT(x, ...)
	#endif
#else
	#error The Spectral Game-Engine yet only supports Windows!
#endif