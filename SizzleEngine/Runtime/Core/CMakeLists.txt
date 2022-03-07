cmake_minimum_required(VERSION 3.21)
 

add_library(EngineCore SHARED
	CoreAPI.h
	
	Util/RefCounter.h
	Util/RefPointer.h

	CoreDebug/DebugMacros.h
	CoreDebug/Private/DebugMacros.cpp


	CoreDebug/Public/ILogContext.h
	CoreDebug/Private/ILogContext.cpp

	Delegate/Delegate.h

	Delegate/EngineDelegates/EngineDelegates.h
	Delegate/EngineDelegates/EngineDelegates.cpp

	Serialization/SArchive.h
	Serialization/SArchive.cpp

	Serialization/Public/SDataSerializer.h
	Serialization/Private/SDataSerializer.cpp

	Threading/Task/Public/Task.h
	Threading/Task/Private/Task.cpp
)

#set_target_properties(EngineCore PROPERTIES LINKER_LANGUAGE CXX)
target_compile_definitions(EngineCore PRIVATE CORE_LIB=3)
target_compile_definitions(EngineCore PRIVATE _WRITE_DEBUG_TO_CONSOLE=3)
set_property(TARGET EngineCore PROPERTY CXX_STANDARD 20)