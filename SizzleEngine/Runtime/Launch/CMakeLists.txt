cmake_minimum_required(VERSION 3.21)



add_executable(SizzleEngine WIN32
				MainLaunch.h
				MainLaunch.cpp
)

set_property(TARGET SizzleEngine PROPERTY CXX_STANDARD 20)

if(WIN32)
	target_sources(SizzleEngine PRIVATE 
		Windows/WinLaunch.cpp
	)
endif()

target_link_libraries(SizzleEngine PRIVATE EngineCore)
target_link_libraries(SizzleEngine PRIVATE EngineObjectCore)
target_link_libraries(SizzleEngine PRIVATE EngineLib)

