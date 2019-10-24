#include "AbstractShape.h"

AbstractShape::AbstractShape(const xml_node<>* node)
{
	if (!node)
		throw runtime_error{ "malformed input, shape node not found" };
	m_materialName = readValue<string>(node->first_node("material"));
}
