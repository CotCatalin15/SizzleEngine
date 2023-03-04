cmake_minimum_required (VERSION 3.21)

if(WIN32)
	set(OS_WINDOWS 1)
	add_compile_definitions(OS_WINDOWS)
endif()

add_executable(render_task_exec render_task_main.cpp)
target_link_libraries(render_task_exec PRIVATE EngineCore)
target_link_libraries(render_task_exec PRIVATE EngineRenderCore)
#target_link_libraries(render_task_exec PRIVATE EngineRenderContext)
#target_link_libraries(render_task_exec PRIVATE VulkanRenderContext)
