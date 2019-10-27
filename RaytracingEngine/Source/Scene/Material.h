#pragma once
#include "Geometry/Vector3.h"
#include "rapidxml.hpp"

using namespace rapidxml;


class Material
{
	Color m_diffuseColor;
	float m_reflectance;
	float m_transparency;
	float m_refractionIndex;
public:
	Material() : m_diffuseColor{ .5, .5, .5 }, m_reflectance{ 0 }, m_transparency{ 0 }, m_refractionIndex{ 1 } {}
	Material(const xml_node<>* node);
	const Color& getColor() const { return m_diffuseColor; }
	float getReflectance() const { return m_reflectance; }
	float getTransparency() const { return m_transparency; }
	float getRefracionIndex() const { return m_refractionIndex; }
};

