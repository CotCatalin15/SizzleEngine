#pragma once

#define echeck(expr, msg, ...) do {\
if(!(expr)){\
	\
}\
} while (0)

#define check(expr) echeck(expr)