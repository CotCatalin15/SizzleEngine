cmake_minimum_required (VERSION 3.21)

if(WIN32)
	set(OS_WINDOWS 1)
	add_compile_definitions(OS_WINDOWS)
endif()

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(RenderingTests)
