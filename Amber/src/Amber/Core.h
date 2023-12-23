#pragma once

#ifdef AM_PLATFORM_WINDOWS
	#ifdef AM_BUILD_DLL
		#define AMBER_API __declspec(dllexport)
	#else 
		#define AMBER_API __declspec(dllimport)
	#endif

#else 
	#error Amber Only Supports Windows!
#endif