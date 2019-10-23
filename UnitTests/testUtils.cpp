#include "pch.h"
#include "testUtils.h"

bool areFloatsEqual(float x, float y)
{
	return abs(x - y) < EPSILON;
}
