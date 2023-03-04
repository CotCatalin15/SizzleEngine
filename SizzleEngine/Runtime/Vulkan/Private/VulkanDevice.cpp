#define VMA_IMPLEMENTATION
#include "VulkanDevice.h"
#include "VulkanWrapper.h"

#include <set>
#include <algorithm>


VulkanDevice::VulkanDevice(VkInstance instance) : 
    m_allocator{ nullptr },
    _handle{ nullptr }
{
    _instance = instance;

    VkDeviceQueueCreateInfo GraphicsDeviceQueue = {};
    VkDeviceQueueCreateInfo ComputeDeviceQueue = {};
    VkDeviceQueueCreateInfo TransferDeviceQueue = {};

    //Get
    {
        uint32_t Count;
        VulkanWrapper::vkEnumeratePhysicalDevices(_instance, &Count, nullptr);

        std::vector<VkPhysicalDevice> PhysicalDevices(Count);

        if (Count == 0)
        {
            vulkan_check(VK_ERROR_INITIALIZATION_FAILED);
        }

        VulkanWrapper::vkEnumeratePhysicalDevices(_instance, &Count, PhysicalDevices.data());


        bool OneSuppGraphics = false;
        std::vector< EPhysicalDeviceProperties > PhysicalDeviceProperties(Count);
        for (uint32_t i = 0; i < Count; ++i)
        {
            auto& EProps = PhysicalDeviceProperties[i];
            EProps.GraphicsQueueProperties.queueFlags = VK_MEMORY_PROPERTY_FLAG_BITS_MAX_ENUM;

            EProps.gpu = PhysicalDevices[i];
            VulkanWrapper::vkGetPhysicalDeviceProperties(EProps.gpu, &EProps.Properties);



            uint32_t QueueCount;
            VulkanWrapper::vkGetPhysicalDeviceQueueFamilyProperties(EProps.gpu, &QueueCount, nullptr);
            std::vector<VkQueueFamilyProperties> QueueProperties(QueueCount);
            VulkanWrapper::vkGetPhysicalDeviceQueueFamilyProperties(EProps.gpu, &QueueCount, QueueProperties.data());
            VulkanWrapper::vkGetPhysicalDeviceMemoryProperties(EProps.gpu, &EProps.MemoryProperties);

            for (uint32_t j = 0; j < QueueCount; ++j)
            {
                //Graphics Bit
                if (QueueProperties[j].queueFlags & VK_QUEUE_GRAPHICS_BIT &&
                    EProps.GraphicsQueueProperties.queueFlags > QueueProperties[j].queueFlags)
                {
                    EProps.GraphicsQueueProperties = QueueProperties[j];
                    EProps.GraphicsIndex = j;
                    OneSuppGraphics = true;
                }
                //Compute bit
                if (QueueProperties[j].queueFlags & VK_QUEUE_COMPUTE_BIT &&
                    EProps.GraphicsQueueProperties.queueFlags > QueueProperties[j].queueFlags)
                {
                    EProps.ComputeQueueProperties = QueueProperties[j];
                    EProps.ComputeIndex = j;
                    EProps.HasCompute = true;
                }

                //Transfer Bit
                if (QueueProperties[j].queueFlags & VK_QUEUE_TRANSFER_BIT &&
                    EProps.TransferQueueProperties.queueFlags > QueueProperties[j].queueFlags)
                {
                    EProps.TransferQueueProperties = QueueProperties[j];
                    EProps.TransferIndex = j;
                    EProps.HasTransfer = true;
                }

            }
        }

        if (!OneSuppGraphics)
        {
            vulkan_check(VK_ERROR_FEATURE_NOT_PRESENT);
        }

        std::sort(PhysicalDeviceProperties.begin(), PhysicalDeviceProperties.end(), [=](const EPhysicalDeviceProperties& lhs, const EPhysicalDeviceProperties& rhs)
            {

                if (lhs.Properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
                    rhs.Properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                    return true;
                if (rhs.Properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
                    lhs.Properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                    return false;

                return lhs.GraphicsQueueProperties.queueFlags > rhs.GraphicsQueueProperties.queueFlags;
            });

        EProperties = std::move(PhysicalDeviceProperties[0]);

    }

    if (!EProperties.HasCompute)
        EProperties.ComputeIndex = EProperties.GraphicsIndex;

    if (!EProperties.HasTransfer)
        EProperties.TransferIndex = EProperties.GraphicsIndex;

    std::vector< VkDeviceQueueCreateInfo > DeviceQueueInfo;
    DeviceQueueInfo.reserve(3);

    float Priorities[1] = { 1.0 };

    {
        std::set<uint32_t> QueueIndices;
        QueueIndices.emplace(EProperties.GraphicsIndex);
        QueueIndices.emplace(EProperties.ComputeIndex);
        QueueIndices.emplace(EProperties.TransferIndex);

        VkDeviceQueueCreateInfo QueueCreateInfo = {};
        for (auto& Index : QueueIndices)
        {
            QueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            QueueCreateInfo.pNext = nullptr;
            QueueCreateInfo.flags = 0;
            QueueCreateInfo.queueFamilyIndex = Index;
            QueueCreateInfo.queueCount = 1;
            QueueCreateInfo.pQueuePriorities = Priorities;

            DeviceQueueInfo.emplace_back(QueueCreateInfo);
        }

    }

    //Get Extensions
    {
        uint32_t Count = 0;
        VulkanWrapper::vkEnumerateDeviceExtensionProperties(EProperties.gpu, nullptr, &Count, nullptr);
        std::vector< VkExtensionProperties > Extensions(Count);
        VulkanWrapper::vkEnumerateDeviceExtensionProperties(EProperties.gpu, nullptr, &Count, Extensions.data());

        //bool bHasDynamicIndexing;

        for (uint32_t i = 0; i < Count; ++i)
        {

            if (strcmp(Extensions[i].extensionName, "VK_KHR_swapchain") == 0)
                DeviceExtensions.emplace_back("VK_KHR_swapchain");
        }
    }


    VkDeviceCreateInfo DeviceCreateInfo = {};
    DeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    DeviceCreateInfo.pNext = nullptr;
    DeviceCreateInfo.flags = 0;
    DeviceCreateInfo.queueCreateInfoCount = (uint32_t)DeviceQueueInfo.size();
    DeviceCreateInfo.pQueueCreateInfos = DeviceQueueInfo.data();

    //Layers are not supported
    DeviceCreateInfo.enabledLayerCount = 0;
    DeviceCreateInfo.ppEnabledLayerNames = nullptr;


    DeviceCreateInfo.enabledExtensionCount = (uint32_t)DeviceExtensions.size();
    DeviceCreateInfo.ppEnabledExtensionNames = DeviceExtensions.data();

    //Features To Enable
    VkPhysicalDeviceFeatures Features = {};
    Features.imageCubeArray = VK_TRUE;
    Features.samplerAnisotropy = VK_TRUE;
    Features.multiDrawIndirect = VK_TRUE;
    Features.logicOp = VK_TRUE;

    DeviceCreateInfo.pEnabledFeatures = &Features;

    vulkan_check(VulkanWrapper::vkCreateDevice(EProperties.gpu, &DeviceCreateInfo, GetVulkanAllocator(), &_handle));

    PostDeviceInit();
}


VulkanDevice::~VulkanDevice()
{
    if (_handle)
    {
        if (m_allocator)
        {
            vmaDestroyAllocator(m_allocator);
        }

        VulkanWrapper::vkDestroyDevice(_handle, GetVulkanAllocator());
        _handle = nullptr;
    }
}

void VulkanDevice::PostDeviceInit()
{
    VulkanWrapper::InitDeviceFunctions(_handle);

    VmaVulkanFunctions memoryFunctions = { 0 };
    VulkanWrapper::FillVmaFunctions(&memoryFunctions);

    VmaAllocatorCreateInfo allocatorCreateInfo = { 0 };
    allocatorCreateInfo.physicalDevice = EProperties.gpu;
    allocatorCreateInfo.device = _handle;
    allocatorCreateInfo.instance = _instance;
    allocatorCreateInfo.pVulkanFunctions = &memoryFunctions;
    allocatorCreateInfo.vulkanApiVersion = VK_API_VERSION_1_3;

    vulkan_check(vmaCreateAllocator(&allocatorCreateInfo, &m_allocator));

    //_graphicsQueue = new FVulkanQueue(this, EProperties.GraphicsIndex);
    //_computeQueue = new FVulkanQueue(this, EProperties.ComputeIndex);
    //_transferQueue = new FVulkanQueue(this, EProperties.TransferIndex);
}
