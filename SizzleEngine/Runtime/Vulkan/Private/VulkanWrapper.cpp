#include "VulkanWrapper.h"
#include "VulkanFunctions.h"

#include <windows.h>
#include "vk_mem_alloc.h"

HMODULE GVulkanLibrary;

namespace VulkanFunctions
{
    ITERATE_DEFAULT_VULKAN_FUNCTIONS(DECLARE_VK_FUNCTION);
    ITERATE_INSTANCE_VULKAN_FUNCTIONS(DECLARE_VK_FUNCTION);
    ITERATE_DEVICE_VULKAN_FUNCTIONS(DECLARE_VK_FUNCTION);
}


void VulkanWrapper::InitVulkanWrapper()
{
    GVulkanLibrary = LoadLibraryA("vulkan-1.dll");
    check(GVulkanLibrary);
    
    //Load default libraries

    ITERATE_DEFAULT_VULKAN_FUNCTIONS(LOAD_DEFAULT_VULKAN_FUNCTIONS);
}

void VulkanWrapper::InitInstanceFunctions(VkInstance Instance)
{
    ITERATE_INSTANCE_VULKAN_FUNCTIONS(LOAD_INSTANCE_VULKAN_FUNCTIONS);
}

void VulkanWrapper::InitDeviceFunctions(VkDevice Device)
{
    ITERATE_DEVICE_VULKAN_FUNCTIONS(LOAD_DEVICE_VULKAN_FUNCTIONS);
}

void VulkanWrapper::UnloadDeviceFunctions()
{
    ITERATE_DEVICE_VULKAN_FUNCTIONS(SET_VULKAN_FUNCTION_TO_NULL);
}

void VulkanWrapper::UnloadVulkanWrapper()
{
    FreeLibrary(GVulkanLibrary);
}

void* VulkanWrapper::LoadDefaultVulkanFunction(const char* Name)
{
    void* fncPtr = GetProcAddress(GVulkanLibrary, Name);
    check(fncPtr);
    return fncPtr;
}

void* VulkanWrapper::LoadInstanceVulkanFunction(VkInstance instance, const char* Name)
{
    void* fncPtr = VulkanWrapper::vkGetInstanceProcAddr(instance, Name);
    check(fncPtr);
    return fncPtr;
}

void* VulkanWrapper::LoadDeviceVulkanFunctions(VkDevice device, const char* Name)
{
    void* fncPtr = VulkanWrapper::vkGetDeviceProcAddr(device, Name);
    check(fncPtr);
    return fncPtr;
}

VkResult VulkanWrapper::vkEnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties)
{
    return VULKAN_FN_NAMESPACE vkEnumerateInstanceLayerProperties(pPropertyCount, pProperties);
}

VkResult VulkanWrapper::vkEnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties)
{
    return VULKAN_FN_NAMESPACE vkEnumerateInstanceExtensionProperties(pLayerName, pPropertyCount, pProperties);
}

VkResult VulkanWrapper::vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance)
{
    return VULKAN_FN_NAMESPACE vkCreateInstance(pCreateInfo, pAllocator, pInstance);
}

void VulkanWrapper::vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator)
{
    return VULKAN_FN_NAMESPACE vkDestroyInstance(instance, pAllocator);
}

void* VulkanWrapper::vkGetInstanceProcAddr(VkInstance instance, const char* pName)
{
    return VULKAN_FN_NAMESPACE vkGetInstanceProcAddr(instance, pName);
}

VkResult VulkanWrapper::vkEnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices)
{
    return VULKAN_FN_NAMESPACE vkEnumeratePhysicalDevices(instance, pPhysicalDeviceCount, pPhysicalDevices);
}

void VulkanWrapper::vkGetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties)
{
    VULKAN_FN_NAMESPACE vkGetPhysicalDeviceMemoryProperties(physicalDevice, pMemoryProperties);
}

void VulkanWrapper::vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties)
{
    VULKAN_FN_NAMESPACE vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

VkResult VulkanWrapper::vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties)
{
    return VULKAN_FN_NAMESPACE vkEnumerateDeviceExtensionProperties(physicalDevice, pLayerName, pPropertyCount, pProperties);
}

void VulkanWrapper::vkGetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures)
{
    VULKAN_FN_NAMESPACE vkGetPhysicalDeviceFeatures2(physicalDevice, pFeatures);
}

void VulkanWrapper::vkGetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties)
{
    VULKAN_FN_NAMESPACE vkGetPhysicalDeviceProperties(physicalDevice, pProperties);
} 

void VulkanWrapper::vkGetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures)
{
    VULKAN_FN_NAMESPACE vkGetPhysicalDeviceFeatures(physicalDevice, pFeatures);
}

VkResult VulkanWrapper::vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice)
{
    return VULKAN_FN_NAMESPACE vkCreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice);
}

void VulkanWrapper::vkDestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator)
{
    VULKAN_FN_NAMESPACE vkDestroyDevice(device, pAllocator);
}

VkResult VulkanWrapper::vkCreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence)
{
    return VULKAN_FN_NAMESPACE vkCreateFence(device, pCreateInfo, pAllocator, pFence);
}

VkResult VulkanWrapper::vkWaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout)
{
    return VULKAN_FN_NAMESPACE vkWaitForFences(device, fenceCount, pFences, waitAll, timeout);
}

VkResult VulkanWrapper::vkResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences)
{
    return VULKAN_FN_NAMESPACE vkResetFences(device, fenceCount, pFences);
}

void VulkanWrapper::vkDestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator)
{
    VULKAN_FN_NAMESPACE vkDestroyFence(device, fence, pAllocator);
}

void* VulkanWrapper::vkGetDeviceProcAddr(VkDevice device, const char* pName)
{
    return VULKAN_FN_NAMESPACE vkGetDeviceProcAddr(device, pName);
}

void VulkanWrapper::vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue)
{
    return VULKAN_FN_NAMESPACE vkGetDeviceQueue(device, queueFamilyIndex, queueIndex, pQueue);
}

VkResult VulkanWrapper::vkAllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory)
{
    return VULKAN_FN_NAMESPACE vkAllocateMemory(device, pAllocateInfo, pAllocator, pMemory);
}

void VulkanWrapper::vkFreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator)
{
    VULKAN_FN_NAMESPACE vkFreeMemory(device, memory, pAllocator);
}

VkResult VulkanWrapper::vkCreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer)
{
    return VULKAN_FN_NAMESPACE vkCreateBuffer(device, pCreateInfo, pAllocator, pBuffer);
}

void VulkanWrapper::vkDestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator)
{
    VULKAN_FN_NAMESPACE vkDestroyBuffer(device, buffer, pAllocator);
}

void VulkanWrapper::vkGetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements)
{
    VULKAN_FN_NAMESPACE vkGetBufferMemoryRequirements(device, buffer, pMemoryRequirements);
}

VkResult VulkanWrapper::vkBindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset)
{
    return VULKAN_FN_NAMESPACE vkBindBufferMemory(device, buffer, memory, memoryOffset);
}

void VulkanWrapper::FillVmaFunctions(VmaVulkanFunctions* Functions)
{
    check(Functions);
    Functions->vkGetInstanceProcAddr = VULKAN_FN_NAMESPACE vkGetInstanceProcAddr;
    Functions->vkGetDeviceProcAddr = VULKAN_FN_NAMESPACE vkGetDeviceProcAddr;
    Functions->vkGetPhysicalDeviceProperties = VULKAN_FN_NAMESPACE vkGetPhysicalDeviceProperties;
    Functions->vkGetPhysicalDeviceMemoryProperties = VULKAN_FN_NAMESPACE vkGetPhysicalDeviceMemoryProperties;
    Functions->vkAllocateMemory = VULKAN_FN_NAMESPACE vkAllocateMemory;
    Functions->vkFreeMemory = VULKAN_FN_NAMESPACE vkFreeMemory;
    Functions->vkMapMemory = VULKAN_FN_NAMESPACE vkMapMemory;
    Functions->vkUnmapMemory = VULKAN_FN_NAMESPACE vkUnmapMemory;
    Functions->vkFlushMappedMemoryRanges = VULKAN_FN_NAMESPACE vkFlushMappedMemoryRanges;
    Functions->vkInvalidateMappedMemoryRanges = VULKAN_FN_NAMESPACE vkInvalidateMappedMemoryRanges;
    Functions->vkBindBufferMemory = VULKAN_FN_NAMESPACE vkBindBufferMemory;
    Functions->vkBindImageMemory = VULKAN_FN_NAMESPACE vkBindImageMemory;
    Functions->vkGetBufferMemoryRequirements = VULKAN_FN_NAMESPACE vkGetBufferMemoryRequirements;
    Functions->vkGetImageMemoryRequirements = VULKAN_FN_NAMESPACE vkGetImageMemoryRequirements;
    Functions->vkCreateBuffer = VULKAN_FN_NAMESPACE vkCreateBuffer;
    Functions->vkDestroyBuffer = VULKAN_FN_NAMESPACE vkDestroyBuffer;
    Functions->vkCreateImage = VULKAN_FN_NAMESPACE vkCreateImage;
    Functions->vkDestroyImage = VULKAN_FN_NAMESPACE vkDestroyImage;
    Functions->vkCmdCopyBuffer = VULKAN_FN_NAMESPACE vkCmdCopyBuffer;
    //Functions->vkGetBufferMemoryRequirements2KHR = VULKAN_FN_NAMESPACE;
    //Functions->vkGetImageMemoryRequirements2KHR = VULKAN_FN_NAMESPACE;
    //Functions->vkBindBufferMemory2KHR = VULKAN_FN_NAMESPACE;
    //Functions->vkBindImageMemory2KHR = VULKAN_FN_NAMESPACE;
    //Functions->vkGetPhysicalDeviceMemoryProperties2KHR = VULKAN_FN_NAMESPACE;
    //Functions->vkGetDeviceBufferMemoryRequirements = VULKAN_FN_NAMESPACE;
    //Functions->vkGetDeviceImageMemoryRequirements = VULKAN_FN_NAMESPACE;
}
