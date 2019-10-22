#pragma once
#include "Geometry/Vector3.h"

class Ray
{
	Vector3 origin;
	Vector3 direction;
public:
	Ray(const Vector3& origin, const Vector3& direction) : origin{ origin }, direction{ direction } {}
	const Vector3& getOrigin() const { return origin; }
	const Vector3& getDirection() const { return direction; }
};

