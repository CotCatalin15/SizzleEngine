cmake_minimum_required(VERSION 3.21)

add_library(EngineLib SHARED)

target_sources(EngineLib PRIVATE 
	EngineAPI.h

	Module/EngineModule.h
	Module/EngineModule.cpp


	Class/SEngine.h
	Class/SEngine.generated.h
	Class/SEngine.cpp
)

target_compile_definitions(EngineLib PRIVATE ENGINE_LIB)
target_link_libraries(EngineLib PRIVATE EngineCore)
target_link_libraries(EngineLib PRIVATE EngineObjectCore)
target_link_libraries(EngineLib PRIVATE EngineRenderContext)
target_link_libraries(EngineLib PRIVATE EngineRenderCore)
