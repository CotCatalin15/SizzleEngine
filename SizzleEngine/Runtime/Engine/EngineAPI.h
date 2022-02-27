#pragma once

#ifdef ENGINE_LIB
	#define ENGINE_API __declspec(dllexport)
#else
	#define ENGINE_API __declspec(dllimport)
#endif