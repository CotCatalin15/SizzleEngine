#pragma once
#include "../Private/VulkanDebug.h"
//#include "../../RenderContext/Public/RenderContext.h"
#include "../VulkanCoreAPI.h"
#include "../../RenderContext/Public/RenderContext.h"

class VulkanDevice;

class VULKANCORE_API VulkanRenderContext : public RenderContext
{
public:
    VulkanRenderContext();

    ~VulkanRenderContext();
private:

    void InitInstance();
    void InitDevice();

    VkInstance m_instance;
    std::unique_ptr<VulkanDevice> m_device;
};