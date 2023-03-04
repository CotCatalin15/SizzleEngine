#pragma once
#include "VulkanDebug.h"

class VulkanDevice;

class VulkanQueue
{
public:
    VulkanQueue();
    VulkanQueue(VulkanDevice* Device, uint32_t FamilyIndex, uint32_t Index);
    ~VulkanQueue() = default;

    inline VkQueue GetHandle() const { return m_handle; }
    inline uint32_t GetFamilyIndex() const { return m_familyIndex; }
    inline VulkanDevice* GetDevice() const { return m_device; }
private:
    VkQueue m_handle;
    uint32_t m_familyIndex;

    VulkanDevice* m_device;
};