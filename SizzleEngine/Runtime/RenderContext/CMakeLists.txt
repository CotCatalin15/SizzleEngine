cmake_minimum_required(VERSION 3.21)

add_library(EngineRenderContext SHARED)

target_sources(EngineRenderContext PRIVATE
	
	RenderContextAPI.h
	

	Public/RenderCommand.h
	Private/RenderCommand.cpp

	Public/RenderContext.h
	Private/RenderContext.cpp
)

target_link_libraries(EngineRenderContext PRIVATE EngineCore) 

target_compile_definitions(EngineRenderContext PRIVATE RENDER_CONTEXT = 1)
target_compile_definitions(EngineRenderContext PRIVATE VULKAN_DEBUG = 1)
set_property(TARGET EngineRenderContext PROPERTY CXX_STANDARD 20)

