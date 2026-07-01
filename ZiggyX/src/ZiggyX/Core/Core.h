#pragma once

#ifdef ZX_PLATFORM_WINDOWS
	#ifdef ZX_BUILD_DLL
		#define ZX_API __declspec(dllexport)
	#else
		#define ZX_API __declspec(dllimport)
	#endif
#else
	#error ZiggyX only supports Windows
#endif