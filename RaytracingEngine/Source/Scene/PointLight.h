#pragma once
#include "rapidxml.hpp"
#include "Geometry/Vector3.h"

using namespace rapidxml;


class PointLight
{
	Vector3f m_position;
	Color m_color;
public:
	PointLight(const xml_node<>* node);
	const Vector3f& getPosition() const { return m_position; }
	const Color& getColor() const { return m_color; }
};

