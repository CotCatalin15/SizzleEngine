#include "VulkanQueue.h"
#include "VulkanDevice.h"
#include "VulkanWrapper.h"

VulkanQueue::VulkanQueue() :
    m_device{ nullptr },
    m_familyIndex{ 0 },
    m_handle{ nullptr }

{}

VulkanQueue::VulkanQueue(VulkanDevice* Device, uint32_t FamilyIndex, uint32_t Index) :
    m_device{ Device },
    m_familyIndex{ FamilyIndex },
    m_handle{ nullptr }
{
    VulkanWrapper::vkGetDeviceQueue(Device->GetHandle(), FamilyIndex, Index, &m_handle);
}


