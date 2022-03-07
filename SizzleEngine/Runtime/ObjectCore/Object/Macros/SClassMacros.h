#pragma once
#include "../Public/SClass.h"

#define BUILD_EXECUTE_COMMAND(Command, ...)

#define BUILD_CLASS(API_NAME, ...) //command ParseClss 

//Some sub-commands have custome names
#define BUILD_EXECUTE_SUBCOMMAND(Command, ...)
#define BUILD_REFLECT(...) //sub_command reflect

#define SERIALIZE_PARAM(...) BUILD_EXECUTE_SUBCOMMAND(Reflex, __VA_ARGS__)