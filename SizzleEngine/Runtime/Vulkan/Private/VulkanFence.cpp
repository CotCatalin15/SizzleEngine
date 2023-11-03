#include "VulkanFence.h"
#include "VulkanWrapper.h"
#include "VulkanDevice.h"
#include "VulkanStats.h"


VulkanFence::VulkanFence(VulkanDevice* Device, bool Signaled) :
    m_handle{ nullptr },
    m_device{ Device }
{
    VkFenceCreateInfo fenceCreateInfo;
    VulkanZeroStruct(fenceCreateInfo, VK_STRUCTURE_TYPE_FENCE_CREATE_INFO);
    fenceCreateInfo.flags = Signaled ? (VK_FENCE_CREATE_SIGNALED_BIT) : (0);

    vulkan_check(VulkanWrapper::vkCreateFence(Device->GetHandle(), &fenceCreateInfo, GetVulkanAllocator(), &m_handle));
}

VulkanFence::~VulkanFence()
{
    if (m_handle)
    {
        VulkanWrapper::vkDestroyFence(m_device->GetHandle(), m_handle, GetVulkanAllocator());
    }
}

bool VulkanFence::IsSignaled() const
{
    VkResult result = VulkanWrapper::vkWaitForFences(m_device->GetHandle(), 1, &m_handle, VK_FALSE, 0);
    switch (result)
    {
    case VK_SUCCESS:
        return true;
    case VK_TIMEOUT:
        return false;
    default:
        vulkan_check(result);
    }

    return false;
}

void VulkanFence::Reset()
{
    VulkanWrapper::vkResetFences(m_device->GetHandle(), 1, &m_handle);
}

VulkanFencePool::VulkanFencePool(VulkanDevice* Device) :
    m_device{ Device }
{
    check(Device);
}

VulkanFencePool::VkFenceHandle VulkanFencePool::AllocateFence(bool Signaled)
{
    std::optional<VkFenceHandle> handle;
    if (Signaled)
    {
        handle = m_fencePool.FindIf([](const VulkanFence& Fence) {
            if (Fence.IsSignaled()) {
                return true;
            }
            return false;
            });
    }
    else
    {
        handle = m_fencePool.Reuse();
    }

    if (handle)
    {
        return std::move(handle.value());
    }

    return m_fencePool.Allocate(m_device, true);
}

void VulkanFencePool::FreeFence(VkFenceHandle Fence)
{
    m_fencePool.Free(std::move(Fence));
}
