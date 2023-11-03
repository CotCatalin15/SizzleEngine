#include "VulkanDebug.h"
#include <memory>
#include "VulkanWrapper.h"
#include "VulkanStats.h"

extern SFileLogContext VulkanLog("VulkanLog.txt");

#ifdef VULKAN_DEBUG

VkBool32 VKAPI_PTR VulkanDebugCallback(
    VkDebugReportFlagsEXT                       flags,
    VkDebugReportObjectTypeEXT                  objectType,
    uint64_t                                    object,
    size_t                                      location,
    int32_t                                     messageCode,
    const char* pLayerPrefix,
    const char* pMessage,
    void* pUserData);


struct VulkanDebugData
{
public:
    VulkanDebugData(VkInstance instance) :
        instance{ instance },
        CreateDebugReportCallback{ nullptr },
        DestroyDebugReportCallback{ nullptr },
        debugHandle{ nullptr }
    {}

    ~VulkanDebugData()
    {
        Disable();
    }

    void Disable()
    {
        if (debugHandle)
        {
            DestroyDebugReportCallback(instance, debugHandle, GetVulkanAllocator());
            debugHandle = nullptr;
        }
    }

    VkInstance instance;

    VkDebugReportCallbackEXT debugHandle;
    PFN_vkCreateDebugReportCallbackEXT CreateDebugReportCallback;
    PFN_vkDestroyDebugReportCallbackEXT DestroyDebugReportCallback;
};

std::unique_ptr<VulkanDebugData> DebugData(nullptr);

void EnableVulkanDebug(VkInstance Instance)
{
    check(Instance);

    DebugData = std::make_unique<VulkanDebugData>(Instance);

    DebugData->CreateDebugReportCallback = 
        (PFN_vkCreateDebugReportCallbackEXT)VulkanWrapper::vkGetInstanceProcAddr(Instance, "vkCreateDebugReportCallbackEXT");

    DebugData->DestroyDebugReportCallback = 
        (PFN_vkDestroyDebugReportCallbackEXT)VulkanWrapper::vkGetInstanceProcAddr(Instance, "vkDestroyDebugReportCallbackEXT");

    if (DebugData->CreateDebugReportCallback == nullptr ||
        DebugData->DestroyDebugReportCallback == nullptr)
    {
        SIZZLE_LOG(VulkanLog, LogVerbosity::Error, "Failed to get debug report callback functions");
    }

    VkDebugReportCallbackCreateInfoEXT debugReportCallbackCreateInfo;
    VulkanZeroStruct(debugReportCallbackCreateInfo, VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT);
    debugReportCallbackCreateInfo.flags = VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
        VK_DEBUG_REPORT_WARNING_BIT_EXT |
        VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
        VK_DEBUG_REPORT_ERROR_BIT_EXT;

    debugReportCallbackCreateInfo.pfnCallback = VulkanDebugCallback;

    vulkan_check(DebugData->CreateDebugReportCallback(Instance, &debugReportCallbackCreateInfo, GetVulkanAllocator(), &DebugData->debugHandle));
}

void DisableVulkanDebug()
{
    DebugData.reset();
}


VkBool32 VKAPI_PTR VulkanDebugCallback(
    VkDebugReportFlagsEXT                       flags,
    VkDebugReportObjectTypeEXT                  objectType,
    uint64_t                                    object,
    size_t                                      location,
    int32_t                                     messageCode,
    const char* pLayerPrefix,
    const char* pMessage,
    void* pUserData)
{
    const char* logFlagType;
    LogVerbosity verbosity = LogVerbosity::Log;

    switch (flags)
    {
    case VK_DEBUG_REPORT_INFORMATION_BIT_EXT:
        logFlagType = "VK_DEBUG_REPORT_INFORMATION_BIT_EXT";
        verbosity = LogVerbosity::Log;
        break;
    case VK_DEBUG_REPORT_WARNING_BIT_EXT:
        logFlagType = "VK_DEBUG_REPORT_WARNING_BIT_EXT";
        verbosity = LogVerbosity::Warning;
        break;
    case VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT:
        logFlagType = "VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT";
        verbosity = LogVerbosity::Warning;
        break;
    case VK_DEBUG_REPORT_ERROR_BIT_EXT:
        logFlagType = "VK_DEBUG_REPORT_ERROR_BIT_EXT";
        verbosity = LogVerbosity::Warning;
        break;
    case VK_DEBUG_REPORT_DEBUG_BIT_EXT:
        logFlagType = "VK_DEBUG_REPORT_DEBUG_BIT_EXT";
        verbosity = LogVerbosity::Warning;
        break;
    default:
        logFlagType = "UNKNOWN";
        verbosity = LogVerbosity::Warning;
        break;
    }

    SIZZLE_LOG(VulkanLog, LogVerbosity::Log, "Debug [Flags: %s][Object: %d] %s", logFlagType, objectType, pMessage);

    return VK_TRUE;
}

#endif