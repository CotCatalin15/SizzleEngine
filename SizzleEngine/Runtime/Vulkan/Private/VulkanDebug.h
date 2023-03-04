#pragma once
#define VK_NO_PROTOTYPES
#include <string.h>
#include "../../Core/CoreDebug/DebugMacros.h"
#include "../../../Thirdparty/Include/Vulkan/vulkan.h"
#include "vk_mem_alloc.h"

extern SFileLogContext VulkanLog;

#define vulkan_check(expr) check_log(VulkanLog, expr == VK_SUCCESS );

template<typename VkStructType>
inline void VulkanZeroStruct(VkStructType& VkStruct, VkStructureType Type)
{
    memset(&VkStruct, 0, sizeof(VkStructType));
    VkStruct.sType = Type;
}

inline VkAllocationCallbacks* GetVulkanAllocator()
{
    return nullptr;
}

#ifdef VULKAN_DEBUG
void EnableVulkanDebug(VkInstance Instance);
void DisableVulkanDebug();
#endif