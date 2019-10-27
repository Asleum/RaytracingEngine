#pragma once
#include "Scene/AbstractShape.h"

using namespace rapidxml;


class Sphere : public AbstractShape
{
	float m_radius;
	Vector3f m_position;
public:
	Sphere(const xml_node<>* node);
	IntersectionResult intersect(const Ray& ray) const;
};

