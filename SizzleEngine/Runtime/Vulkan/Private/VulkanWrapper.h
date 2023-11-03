#pragma once


#include "VulkanDebug.h"


class VulkanWrapper
{
public:

    static void InitVulkanWrapper();
    static void InitInstanceFunctions(VkInstance Instance);
    static void InitDeviceFunctions(VkDevice Device);
    static void UnloadDeviceFunctions();
    static void UnloadVulkanWrapper();

    static void* LoadDefaultVulkanFunction(const char* Name);
    static void* LoadInstanceVulkanFunction(VkInstance instance, const char* Name);
    static void* LoadDeviceVulkanFunctions(VkDevice device, const char* Name);

    static VkResult vkEnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties);
    static VkResult vkEnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties);
    static VkResult vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance);
    static void     vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator);
    static void*    vkGetInstanceProcAddr(VkInstance instance, const char* pName);

    static VkResult vkEnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices);
    static void     vkGetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties);
    static void     vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties);
    static VkResult vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties);
    static void     vkGetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures);
    static void     vkGetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties);
    static void     vkGetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures);
    static VkResult vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice);
    static void     vkDestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator);

    static VkResult vkCreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence);
    static void     vkDestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator);

    static void* vkGetDeviceProcAddr(VkDevice device, const char* pName);
    static void vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue);
    static VkResult vkAllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory);
    static void vkFreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator);

    static void FillVmaFunctions(struct VmaVulkanFunctions* Functions);
private:
};
