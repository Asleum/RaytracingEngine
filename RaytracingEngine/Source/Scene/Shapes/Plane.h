#pragma once
#include "Scene/AbstractShape.h"
#include "Geometry/Vector3.h"
#include "rapidxml.hpp"

using namespace rapidxml;


class Plane :
	public AbstractShape
{
	Vector3f position;
	Vector3f normal;
public:
	Plane(const xml_node<>* node);
};

