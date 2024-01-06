#pragma once

#include <memory>

#ifdef AM_PLATFORM_WINDOWS
	#if AM_DYNAMIC_LINK
		#ifdef AM_BUILD_DLL
			#define AMBER_API __declspec(dllexport)
		#else 
			#define AMBER_API __declspec(dllimport)
		#endif
	#else 
		#define AMBER_API
	#endif
#else 
	#error Amber Only Supports Windows!

#endif

#ifdef AM_DEBUG
	#define AM_ENABLE_ASSERTS
#endif

#ifdef AM_ENABLE_ASSERTS
	#define AM_CORE_ASSERT(x, ...) { if(!(x)) { AM_CORE_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak(); } }
	#define AM_ASSERT(x, ...) { if(!(x)) { AM_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak(); } }

#else
	#define AM_CORE_ASSERT(x,...)
	#define AM_ASSERT(x,...)
#endif
 
#define BIT(x) (1 << x)

#define AM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


namespace Amber
{

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}
