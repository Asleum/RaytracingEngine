#pragma once
#include "Geometry/Ray.h"

struct IntersectionResult {
	Vector3f position;
	Vector3f surfaceNormal;
	float distance;
	bool intersects{ false };
};

class AbstractShape
{
public:
	virtual IntersectionResult intersect(const Ray& ray) const = 0;
};

