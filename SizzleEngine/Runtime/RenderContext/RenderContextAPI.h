#pragma once

#ifdef RENDER_CONTEXT
#define RENDERCONTEXT_API __declspec(dllexport)
#else
#define RENDERCONTEXT_API __declspec(dllimport)
#endif