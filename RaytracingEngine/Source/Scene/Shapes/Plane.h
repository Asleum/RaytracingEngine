#pragma once
#include "Scene/AbstractShape.h"

using namespace rapidxml;


class Plane : public AbstractShape
{
	Vector3f m_position;
	Vector3f m_normal;
public:
	Plane(const xml_node<>* node);
	IntersectionResult intersect(const Ray& ray) const;
};

