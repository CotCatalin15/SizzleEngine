#pragma once

#ifdef RENDERING_CORE
#define RENDERCORE_API __declspec(dllexport)
#else
#define RENDERCORE_API __declspec(dllimport)
#endif