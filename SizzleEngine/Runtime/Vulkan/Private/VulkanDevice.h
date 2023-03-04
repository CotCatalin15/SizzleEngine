#include "VulkanDebug.h"

#include <vector>

class VulkanDevice
{
public:
    VulkanDevice(VkInstance instance);

    ~VulkanDevice();

    inline VkDevice GetHandle() const { return _handle; }

    //inline class FVulkanQueue* GetGraphicsQueue() const { return _graphicsQueue; }
    //inline class FVulkanQueue* GetComputeQueue() const { return _computeQueue; }
    //inline class FVulkanQueue* GetTransferQueue() const { return _transferQueue; }

    inline VkPhysicalDevice GetPhysicalDevice() const { return EProperties.gpu; }
    inline VkPhysicalDeviceProperties const& GetPhysicalDeviceProperties() const { return EProperties.Properties; }
    inline VkPhysicalDeviceMemoryProperties const& GetMemoryProperties() const { return EProperties.MemoryProperties; }

    inline VmaAllocator GetAllocator() { return m_allocator; }

private:
    void PostDeviceInit();
    
    VkDevice _handle;
    VmaAllocator m_allocator;

    //class FVulkanQueue* _graphicsQueue;
    //class FVulkanQueue* _computeQueue;
    //class FVulkanQueue* _transferQueue;

    VkInstance _instance;
    std::vector< const char* > DeviceExtensions;

    struct EPhysicalDeviceProperties
    {
        EPhysicalDeviceProperties() :
            GraphicsQueueProperties{ PropertiesArray[0] },
            ComputeQueueProperties{ PropertiesArray[1] },
            TransferQueueProperties{ PropertiesArray[2] }
        {}

        EPhysicalDeviceProperties& operator=(const EPhysicalDeviceProperties& other)
        {
            gpu = other.gpu;
            Properties = other.Properties;
            MemoryProperties = other.MemoryProperties;
            HasCompute = other.HasCompute;
            GraphicsIndex = other.GraphicsIndex;
            ComputeIndex = other.ComputeIndex;
            PropertiesArray[0] = other.PropertiesArray[0];
            PropertiesArray[1] = other.PropertiesArray[1];
            PropertiesArray[2] = other.PropertiesArray[2];

            return *this;
        }

        bool HasCompute = false;
        bool HasTransfer = false;

        VkPhysicalDevice gpu = nullptr;
        VkPhysicalDeviceProperties Properties = {};
        VkPhysicalDeviceMemoryProperties MemoryProperties = {};
        VkQueueFamilyProperties PropertiesArray[3] = {};

        VkQueueFamilyProperties& GraphicsQueueProperties;
        VkQueueFamilyProperties& ComputeQueueProperties;
        VkQueueFamilyProperties& TransferQueueProperties;

        uint32_t GraphicsIndex;
        uint32_t ComputeIndex;
        uint32_t TransferIndex;
    }EProperties;
};