#include "PointLight.h"
#include <iostream>

PointLight::PointLight(const xml_node<>* node)
{
	if (!node)
		throw runtime_error{ "malformed input, sphere node not found" };
	m_position = Vector3f{ node->first_node("position") };
	m_color = Color{ node->first_node("color"), "r", "g", "b" } / 255;
}
