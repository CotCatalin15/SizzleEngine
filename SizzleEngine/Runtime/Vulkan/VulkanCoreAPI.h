#pragma once

#ifdef VULKAN_DEBUG
#define VULKANCORE_API __declspec(dllexport)
#else
#define VULKANCORE_API __declspec(dllimport)
#endif