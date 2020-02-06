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