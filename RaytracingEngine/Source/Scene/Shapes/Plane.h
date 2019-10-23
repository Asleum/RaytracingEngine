#pragma once
#include "Scene/AbstractShape.h"
#include "Geometry/Vector3.h"
#include "rapidxml.hpp"

using namespace rapidxml;


class Plane :
	public AbstractShape
{
	Vector3f m_position;
	Vector3f m_normal;
public:
	Plane(const xml_node<>* node);
	IntersectionResult intersect(const Ray& ray) const;
};

