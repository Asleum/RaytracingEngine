#pragma once
#include "Geometry/Vector3.h"


class Ray
{
	Vector3f m_origin;
	Vector3f m_direction;
public:
	Ray(const Vector3f& from, const Vector3f& to) : m_origin{ from }, m_direction{ (to - from).normalized() } {}
	const Vector3f& getOrigin() const { return m_origin; }
	const Vector3f& getDirection() const { return m_direction; }
};

