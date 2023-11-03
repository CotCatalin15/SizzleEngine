#pragma once
#include "VulkanDebug.h"

class VulkanDevice;

class VulkanBuffer
{
public:
    VulkanBuffer(VulkanDevice* Device, VkDeviceSize BufferSize, VkBufferUsageFlags UsageFlags);
    ~VulkanBuffer();

    inline VkDeviceSize GetSize() const { return m_bufferSize; }
    inline VkBufferUsageFlags GetFlags() const { return m_usageFlags; }

private:
    VkBuffer m_buffer;
    VulkanDevice* m_device;

    VkDeviceSize m_bufferSize;
    VkBufferUsageFlags m_usageFlags;
};

