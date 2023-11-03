#pragma once
#include "VulkanDebug.h"

#include <list>
#include <mutex>
#include "../../Core/Pools/MemoryPool.h"


class VulkanDevice;

class VulkanFence
{
public:
    VulkanFence(VulkanFence&& other);
    ~VulkanFence();

    VkFence GetHandle() { return m_handle; }
private:
    VulkanFence(VulkanDevice* Device, bool Signaled);

    VkFence m_handle;
    VulkanDevice* m_device;

    friend class VulkanFencePool;
};

class VulkanFencePool
{
public:
    using VkFenceHandle = Core::Pool::SimpleReusePool<VulkanFence>::ReuseHandle;

    VulkanFencePool(VulkanDevice* Device);
    ~VulkanFencePool() = default;

    VulkanDevice* GetDevice() { return m_device; }

    VkFenceHandle AllocateFence(bool Signaled);
    void FreeFence(VkFenceHandle Fence);

private:

    VulkanDevice* m_device;

    Core::Pool::SimpleReusePool<VulkanFence> m_fencePool;
};