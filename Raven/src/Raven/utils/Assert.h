#pragma once
#include <Raven/logger/Logger.h>

#if defined(RAVEN_ASSERT_INCLUDE_HEADER)
#if defined(DEBUG)
	#define ENABLE_ASSERTS
#endif
#ifdef ENABLE_ASSERTS
	#define ASSERT(x, ...) { if(!(x)) { LOG_ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ASSERT(x, ...)
#endif
#else
#error Include this file via Core.h
#endif