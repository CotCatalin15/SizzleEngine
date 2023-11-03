cmake_minimum_required(VERSION 3.21)

add_library(VulkanRenderContext SHARED)

target_sources(VulkanRenderContext PRIVATE
	VulkanExportModule.h
	VulkanExportModule.cpp
	VulkanCoreAPI.h

	Private/VulkanDebug.h
	Private/VulkanDebug.cpp
	Private/VulkanFunctions.h
	Private/VulkanWrapper.h
	Private/VulkanWrapper.cpp
	Private/VulkanDevice.h
	Private/VulkanDevice.cpp
	Private/VulkanQueue.h
	Private/VulkanQueue.cpp
	Private/vk_mem_alloc.h
	Private/Vulkanfence.h
	Private/Vulkanfence.cpp

	Public/VulkanRenderContext.h
	Private/VulkanRenderContext.cpp
 "Private/VulkanFence.h" "Private/VulkanFence.cpp" "Private/VulkanStats.h")

target_link_libraries(VulkanRenderContext PRIVATE EngineCore) 
target_link_libraries(VulkanRenderContext PRIVATE EngineRenderContext) 

target_compile_definitions(VulkanRenderContext PRIVATE VULKAN_DEBUG = 1)
target_compile_definitions(VulkanRenderContext PRIVATE VULKAN_MEMORY_ORDER_SANITY_CHECK = 1)
set_property(TARGET VulkanRenderContext PROPERTY CXX_STANDARD 20)

