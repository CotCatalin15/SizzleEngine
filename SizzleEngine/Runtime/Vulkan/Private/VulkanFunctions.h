#pragma once

#include "VulkanDebug.h"



#define VULKAN_FN_NAMESPACE VulkanFunctions::

#define GET_VULKAN_FUNCTION_POINTER(Name) PFN_##Name
#define GET_VULKAN_FUNCTION_NAME(Name) Name

#define DECLARE_VK_FUNCTION(Name) GET_VULKAN_FUNCTION_POINTER(Name) GET_VULKAN_FUNCTION_NAME(Name);


//Loaders
#define LOAD_DEFAULT_VULKAN_FUNCTIONS(Name) VULKAN_FN_NAMESPACE GET_VULKAN_FUNCTION_NAME(Name) = ( GET_VULKAN_FUNCTION_POINTER(Name) )VulkanWrapper::LoadDefaultVulkanFunction(#Name);
#define LOAD_INSTANCE_VULKAN_FUNCTIONS(Name) VULKAN_FN_NAMESPACE GET_VULKAN_FUNCTION_NAME(Name) = ( GET_VULKAN_FUNCTION_POINTER(Name) )VulkanWrapper::LoadInstanceVulkanFunction(Instance, #Name);
#define LOAD_DEVICE_VULKAN_FUNCTIONS(Name) VULKAN_FN_NAMESPACE GET_VULKAN_FUNCTION_NAME(Name) = ( GET_VULKAN_FUNCTION_POINTER(Name) )VulkanWrapper::LoadDeviceVulkanFunctions(Device, #Name);
#define SET_VULKAN_FUNCTION_TO_NULL(Name) VULKAN_FN_NAMESPACE GET_VULKAN_FUNCTION_NAME(Name) = ( GET_VULKAN_FUNCTION_POINTER(Name) )nullptr;


//Going over all functions
#define ITERATE_DEFAULT_VULKAN_FUNCTIONS(X)\
	X(vkEnumerateInstanceExtensionProperties);\
	X(vkEnumerateInstanceLayerProperties);\
	X(vkCreateInstance);\
	X(vkDestroyInstance);\
	X(vkGetInstanceProcAddr);

#define ITERATE_INSTANCE_VULKAN_FUNCTIONS(X)\
	X(vkGetDeviceProcAddr);\
	X(vkEnumeratePhysicalDevices);\
	X(vkGetPhysicalDeviceProperties);	\
	X(vkGetPhysicalDeviceMemoryProperties);	\
	X(vkGetPhysicalDeviceQueueFamilyProperties);\
	X(vkEnumerateDeviceExtensionProperties);\
	X(vkCreateDevice);\
	X(vkGetPhysicalDeviceFeatures2); \
	X(vkGetPhysicalDeviceFeatures);

#define ITERATE_DEVICE_VULKAN_FUNCTIONS(X)\
	X(vkDestroyDevice);\
	X(vkGetDeviceQueue);\
	X(vkCreateFence);\
	X(vkDestroyFence);\
	X(vkAllocateMemory);\
	X(vkFreeMemory);\
	X(vkMapMemory);\
	X(vkUnmapMemory);\
	X(vkFlushMappedMemoryRanges);\
	X(vkInvalidateMappedMemoryRanges);\
	X(vkBindBufferMemory);\
	X(vkBindImageMemory);\
	X(vkGetBufferMemoryRequirements);\
	X(vkGetImageMemoryRequirements);\
	X(vkCreateBuffer);\
	X(vkDestroyBuffer);\
	X(vkCreateImage);\
	X(vkDestroyImage);\
	X(vkCmdCopyBuffer);
	