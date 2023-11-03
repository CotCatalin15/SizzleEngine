#include "VulkanBuffer.h"

#include "VulkanDevice.h"
#include "VulkanWrapper.h"

VulkanBuffer::VulkanBuffer(VulkanDevice* Device, VkDeviceSize BufferSize, VkBufferUsageFlags UsageFlags) :
    m_buffer{ nullptr },
    m_device{ Device },
    m_bufferSize{ BufferSize },
    m_usageFlags{ UsageFlags }
{
    VkBufferCreateInfo bufferCreateInfo;
    VulkanZeroStruct(bufferCreateInfo, VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO);
    bufferCreateInfo.size = BufferSize;
    bufferCreateInfo.usage = UsageFlags;
    bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    vulkan_check(VulkanWrapper::vkCreateBuffer(Device->GetHandle(), &bufferCreateInfo, GetVulkanAllocator(), &m_buffer));

    VkMemoryRequirements memoryRequirements = { 0 };
    VulkanWrapper::vkGetBufferMemoryRequirements(Device->GetHandle(), m_buffer, &memoryRequirements);


}

VulkanBuffer::~VulkanBuffer()
{
    if (m_buffer)
    {
        VulkanWrapper::vkDestroyBuffer(m_device->GetHandle(), m_buffer, GetVulkanAllocator());
    }
}
