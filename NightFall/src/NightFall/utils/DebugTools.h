#pragma once
#include "Assert.h"

#ifndef DIST
	#ifdef PLATFORM_WINDOWS
		#define CONSOLE_TITLE(string_)	std::string cmd = "title Console Output of: ";\
										cmd.append(string_);\
										system((const char*)cmd.c_str());
		#define PAUSE()	system("pause");
	#else 
		#error The NightFall Game-Engine yet only supports Windows!
	#endif
#else
	#define CONSOLE_TITLE(string_)
	#define PAUSE()
#endif