cmake_minimum_required(VERSION 3.21)


set(EXECUTABLE_NAME SizzleEngine)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(Core)
add_subdirectory(ObjectCore)
add_subdirectory(Engine)

#independent libraries
add_subdirectory(RenderCore)
add_subdirectory(RenderContext)

#graphics api libs
add_subdirectory(Vulkan)

add_subdirectory(Launch)