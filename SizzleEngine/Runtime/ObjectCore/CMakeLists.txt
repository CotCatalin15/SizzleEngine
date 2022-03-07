cmake_minimum_required(VERSION 3.21)

add_library(EngineObjectCore SHARED)

target_sources(EngineObjectCore PRIVATE
	Object/Macros/SClassMacros.h

	Object/Object.h
	Object/SObjectRegistry.h
	Object/SObjectRegistry.cpp

	Object/Private/Object.cpp
	Object/ObjectCast.h
	Object/Public/SClass.h
	Object/Private/SClass.cpp
	Object/Public/SField.h
	Object/Private/SField.cpp


)

target_link_libraries(EngineObjectCore PRIVATE EngineCore)
target_compile_definitions(EngineObjectCore PRIVATE OBJECTCORE_LIB = 1)
set_property(TARGET EngineObjectCore PROPERTY CXX_STANDARD 20)
