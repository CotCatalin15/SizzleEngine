#include "VulkanFence.h"
#include "VulkanWrapper.h"
#include "VulkanDevice.h"

VulkanFence::VulkanFence(VulkanDevice* Device, bool Signaled) :
    m_handle{ nullptr },
    m_device{ Device }
{
    VkFenceCreateInfo fenceCreateInfo;
    VulkanZeroStruct(fenceCreateInfo, VK_STRUCTURE_TYPE_FENCE_CREATE_INFO);
    fenceCreateInfo.flags = Signaled ? (VK_FENCE_CREATE_SIGNALED_BIT) : (0);

    vulkan_check(VulkanWrapper::vkCreateFence(Device->GetHandle(), &fenceCreateInfo, GetVulkanAllocator(), &m_handle));
}

VulkanFence::VulkanFence(VulkanFence&& other)
{
    this->m_device = other.m_device;
    this->m_handle = other.m_handle;

    other.m_device = nullptr;
    other.m_handle = nullptr;
}

VulkanFence::~VulkanFence()
{
    if (m_handle)
    {
        VulkanWrapper::vkDestroyFence(m_device->GetHandle(), m_handle, GetVulkanAllocator());
    }
}

VulkanFencePool::VulkanFencePool(VulkanDevice* Device) :
    m_device{ Device }
{
    check(Device);
}

VulkanFencePool::VkFenceHandle VulkanFencePool::AllocateFence(bool Signaled)
{
    return m_fencePool.Allocate(std::move(VulkanFence(m_device, Signaled)));
}

void VulkanFencePool::FreeFence(VkFenceHandle Fence)
{
    m_fencePool.Free(std::move(Fence));
}
