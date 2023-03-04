cmake_minimum_required(VERSION 3.21)

add_library(EngineRenderCore SHARED)

target_sources(EngineRenderCore PRIVATE
	RenderCoreAPI.h

	Public/RenderTask.h

	Public/RenderThread.h
	Private/RenderThread.cpp
	 
	Public/RenderTaskContext.h
	Private/RenderTaskContext.cpp
)

target_link_libraries(EngineRenderCore PRIVATE EngineCore)
target_link_libraries(EngineRenderCore PRIVATE EngineRenderContext)
target_link_libraries(EngineRenderCore PRIVATE VulkanRenderContext)
target_compile_definitions(EngineRenderCore PRIVATE RENDERING_CORE=1)
set_property(TARGET EngineRenderCore PROPERTY CXX_STANDARD 20)