#pragma once
#define VK_NO_PROTOTYPES
#include <string.h>
#include "../../Core/CoreDebug/DebugMacros.h"
#include "../../../Thirdparty/Include/Vulkan/vulkan.h"
#include "VulkanStats.h"
#include "vk_mem_alloc.h"

extern SFileLogContext VulkanLog;

#define vulkan_check(expr) do {\
    VkResult result = (expr);\
    echeck_log(VulkanLog, (result) == VK_SUCCESS, "Result: %d", result );\
}while(0)

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