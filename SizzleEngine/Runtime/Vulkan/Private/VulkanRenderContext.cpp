#include "../Public/VulkanRenderContext.h"
#include "VulkanWrapper.h"
#include <vector>
#include <string.h>
#include "VulkanDevice.h"
#include <windows.h>

VulkanRenderContext::VulkanRenderContext() :
    m_instance{ nullptr }
{
    VulkanWrapper::InitVulkanWrapper();
    InitInstance();
    InitDevice();
}

VulkanRenderContext::~VulkanRenderContext()
{
    if (m_instance)
    {
#ifdef VULKAN_DEBUG
        DisableVulkanDebug();
#endif
        m_device.reset();
        
        VulkanWrapper::vkDestroyInstance(m_instance, GetVulkanAllocator());
        m_instance = nullptr;
    }
    
}

void VulkanRenderContext::InitInstance()
{
    std::vector<const char*> instanceExtensions;
    std::vector<const char*> instanceLayers;

    {
        uint32_t Count = 0;
        VulkanWrapper::vkEnumerateInstanceExtensionProperties(nullptr, &Count, nullptr);
        std::vector<VkExtensionProperties> Properties(Count);
        VulkanWrapper::vkEnumerateInstanceExtensionProperties(nullptr, &Count, Properties.data());

        for (uint32_t i = 0; i < Properties.size(); ++i)
        {
            SIZZLE_LOG(VulkanLog, LogVerbosity::Log, "Instance extensions: %s", Properties[i].extensionName);
        }

        instanceExtensions.emplace_back("VK_KHR_surface");
        instanceExtensions.emplace_back("VK_KHR_win32_surface");

#ifdef VULKAN_DEBUG
        instanceExtensions.emplace_back("VK_EXT_debug_report");
        instanceExtensions.emplace_back("VK_EXT_debug_utils");
#endif
    }

    {
        uint32_t Count = 0;
        VulkanWrapper::vkEnumerateInstanceLayerProperties(&Count, nullptr);
        std::vector<VkLayerProperties> Properties(Count);
        VulkanWrapper::vkEnumerateInstanceLayerProperties(&Count, Properties.data());

        for (uint32_t i = 0; i < Properties.size(); ++i)
        {
            SIZZLE_LOG(VulkanLog, LogVerbosity::Log, "Instance layers: %s", Properties[i].layerName);
        }
#ifdef VULKAN_DEBUG
        instanceLayers.emplace_back("VK_LAYER_KHRONOS_validation");
#endif

    }

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.pApplicationName = "";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "SizzleEngine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;


    VkInstanceCreateInfo instanceCreateInfo = {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext = nullptr;
    instanceCreateInfo.flags = 0;
    instanceCreateInfo.pApplicationInfo = &appInfo;
    instanceCreateInfo.enabledLayerCount = (uint32_t)instanceLayers.size();
    instanceCreateInfo.ppEnabledLayerNames = instanceLayers.data();
    instanceCreateInfo.enabledExtensionCount = (uint32_t)instanceExtensions.size();
    instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();

    vulkan_check(VulkanWrapper::vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance));

#ifdef VULKAN_DEBUG
    EnableVulkanDebug(m_instance);
#endif
    VulkanWrapper::InitInstanceFunctions(m_instance);
}

void VulkanRenderContext::InitDevice()
{
    m_device = std::move(std::make_unique<VulkanDevice>(m_instance));
}
