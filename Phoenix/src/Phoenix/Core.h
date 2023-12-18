#pragma once

#ifdef PN_PLATFORM_WINDOWS
	#ifdef PN_BUILD_DLL
		#define PHOENIX_API __declspec(dllexport)
	#else
		#define PHOENIX_API __declspec(dllimport)
	#endif 
#else
	#error Phoenix only supports Windows.
#endif