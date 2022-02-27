# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.21)


set (CMAKE_CXX_STANDARD 17)
project ("SizzleEngine" VERSION 1.0 LANGUAGES CXX)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(ENABLE_CONSOLE 1)
	add_compile_definitions(ENABLE_CONSOLE)
endif()

set(VS_DEBUGGER_COMMAND_ARGUMENTS "Hello")
set(ENGINE_NAME "SizzleEngine")
add_compile_definitions(ENGINE_NAME)



# Include sub-projects.
add_subdirectory ("SizzleEngine")

