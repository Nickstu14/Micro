#pragma once

#ifdef MC_PLATFORM_WINDOWS
	#ifdef MC_BUILD_DLL
		#define MICRO_API	__declspec(dllexport)
	#else
		#define MICRO_API	__declspec(dllimport)
	#endif
#else
	#error Micro only supports windows!
#endif

#ifdef MC_ENABLE_ASSERTS
	#define MC_ASSERT(x, ...) {if(!(x)) { MC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define MC_CORE_ASSERT(x, ...) {if(!(x)) { MC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define MC_ASSERT(x, ...)
	#define MC_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1<< x)