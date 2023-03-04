cmake_minimum_required (VERSION 3.21)

if(WIN32)
	set(OS_WINDOWS 1)
	add_compile_definitions(OS_WINDOWS)
endif()

add_subdirectory(Runtime)  
add_subdirectory(Tests)  