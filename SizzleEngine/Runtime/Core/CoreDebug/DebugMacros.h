#pragma once
#include "../CoreAPI.h"
#include "Public/ILogContext.h"


extern CORE_API SFileLogContext __CheckFileContext;


#define echeck(expr, msg, ...) do {\
if(!(expr)){\
	__CheckFileContext.LogMessageFormat(LogVerbosity::Error, msg, __VA_ARGS__);\
}\
} while (0)

#define check(expr) echeck(expr, "Failed expresion: %s\tFile:%s Line:%d", #expr, __FILE__, __LINE__)

#define SIZZLE_LOG(verbosity, msg, ...) __CheckFileContext.LogMessageFormat(verbosity, msg, __VA_ARGS__)