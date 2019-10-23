#pragma once
#include "Scene/AbstractShape.h"
#include "Geometry/Vector3.h"
#include "rapidxml.hpp"

class Sphere :
	public AbstractShape
{
	float radius;
	Vector3f position;
public:
	Sphere(const xml_node<>* node);
};

