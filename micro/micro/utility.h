#ifndef UTILITY_H
#define UTILITY_H

#include "integer.h"

u8 max(u8 a, u8 b)
{
	return a > b ? a : b;
}

u8 min(u8 a, u8 b)
{
	return a > b ? b : a;
}

#endif // UTILITY_H