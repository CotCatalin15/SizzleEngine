cmake_minimum_required(VERSION 3.21)


add_library(EngineCore SHARED
	CoreAPI.h
	
	Debug/DebugMacros.h
	Debug/Public/SLogContext.h
	Debug/Private/SLogContext.cpp
	
	Serialization/SArchive.h
	Serialization/SArchive.cpp

	Serialization/Public/SDataSerializer.h
	Serialization/Private/SDataSerializer.cpp
)

#set_target_properties(EngineCore PROPERTIES LINKER_LANGUAGE CXX)
target_compile_definitions(EngineCore PRIVATE CORE_LIB=3)
set_property(TARGET EngineCore PROPERTY CXX_STANDARD 20)