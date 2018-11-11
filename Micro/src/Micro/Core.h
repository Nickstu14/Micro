#pragma once

#ifdef MC_PLATFORM_WINDOWS
	#ifdef MC_BUILD_DLL
		#define MICRO_API	_declspec(dllexport)
	#else
		#define MICRO_API	_declspec(dllimport)
	#endif
#else
	#error Micro only supports windows!
#endif