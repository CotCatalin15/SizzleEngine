#pragma once
#include "../Public/SClass.h"

#define BUILD_EXECUTE_COMMAND(Command, ...)
#define BUILD_EXECUTE_SUBCOMMAND(Command, ...)

#define SERIALIZE_PARAM(...) BUILD_EXECUTE_SUBCOMMAND(Reflex, __VA_ARGS__)