#pragma once
#include "Geometry/Ray.h"
#include "rapidxml.hpp"

using namespace rapidxml;


struct IntersectionResult {
	Vector3f position;
	Vector3f surfaceNormal;
	string materialName;
	float distance;
	bool intersects{ false };
	bool inside;
};

class AbstractShape
{
protected:
	string m_materialName;
public:
	AbstractShape(const xml_node<>* node);
	virtual ~AbstractShape() = default;
	virtual IntersectionResult intersect(const Ray& ray) const = 0;
	const string& getMaterialName() const { return m_materialName; }
};

