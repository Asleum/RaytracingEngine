#include "Material.h"
#include "Utils/xmlUtils.h"

Material::Material(const xml_node<>* node)
{
	if (!node)
		throw runtime_error{ "malformed input, material node not found" };
	m_diffuseColor = Vector3f{ node->first_node("color"), "r", "g", "b" } / 255;
	m_reflectance = readValue<float>(node->first_node("reflectance"));
	m_transparency = readValue<float>(node->first_node("transparency"));
	m_refractionIndex = readValue<float>(node->first_node("refractionIndex"));
}
