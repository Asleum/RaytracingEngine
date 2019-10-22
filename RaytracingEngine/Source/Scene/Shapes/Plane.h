#pragma once
#include "Scene/AbstractShape.h"
#include "Geometry/Vector3.h"
#include "rapidxml.hpp"

using namespace rapidxml;


class Plane :
	public AbstractShape
{
	Vector3 position;
	Vector3 normal;
public:
	Plane(const xml_node<>* node);
};

