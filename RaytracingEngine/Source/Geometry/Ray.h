#pragma once
#include "Geometry/Vector3.h"

class Ray
{
	Vector3f origin;
	Vector3f direction;
public:
	Ray(const Vector3f& from, const Vector3f& to) : origin{ from }, direction{ (to - from).normalized() } {}
	const Vector3f& getOrigin() const { return origin; }
	const Vector3f& getDirection() const { return direction; }
};

