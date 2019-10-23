#pragma once
#include "Geometry/Vector3.h"

const float EPSILON{ .0001f };


bool areFloatsEqual(float x, float y);

template <typename T>
bool operator==(const Vector3<T>& v1, const Vector3<T>& v2)
{
	return abs(v1.getX() - v2.getX()) < EPSILON && abs(v1.getY() - v2.getY()) < EPSILON && abs(v1.getZ() - v2.getZ()) < EPSILON;
};