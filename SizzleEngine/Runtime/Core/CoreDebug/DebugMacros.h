#pragma once
#include "../CoreAPI.h"
#include "Public/ILogContext.h"

extern CORE_API SFileLogContext DefaultLog;

#define echeck_log(log, expr, msg, ...)	do {\
if(!(expr)){\
	log.LogMessageFormat(LogVerbosity::Error, msg, __VA_ARGS__);\
}\
} while (0)

#define echeck(expr, msg, ...) echeck_log(DefaultLog, expr, msg, __VA_ARGS__)

#define check_log(log, expr) echeck_log(log, expr, "Failed expresion: %s\tFile:%s Line:%d", #expr, __FILE__, __LINE__)
#define check(expr) check_log(DefaultLog, expr)

#define SIZZLE_LOG(log, verbosity, msg, ...) log.LogMessageFormat(verbosity, msg, __VA_ARGS__)