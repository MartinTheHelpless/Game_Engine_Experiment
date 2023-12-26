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

#ifdef AM_ENABLE_ASSERTS
	#define AM_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak(); } }
	#define AM_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak(); } }

#else
	#define AM_CORE_ASSERT(x,...)
	#define AM_ASSERT(x,...)
#endif
 
#define BIT(x) (1 << x)