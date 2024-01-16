#pragma once

#include <memory>


#ifdef _WIN32
	#define AM_PLATFORM_WINDOWS 
#ifdef _WIN64 
	#define AM_PLATFORM_WINDOWS
#else 
	#error "x86 Builds are not supported!"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR == 1
	#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
	#define AM_PLATFORM_IOS
	#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
	#define AM_PLATFORM_MACOS
	#error "MacOS is not supported!"
#else
	#error "Unknown Apple platform!"
#endif 
#elif defined(__ANDROID__)
	#define AM_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define AM_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
/* Unknown compiler/platform */
#error "Unknown platform!"
#endif // End of platform detection


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

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
 