#pragma once

#ifdef OBJECTCORE_LIB
	#define OBJECTCORE_API __declspec(dllexport)
#else
	#define OBJECTCORE_API __declspec(dllimport)
#endif
