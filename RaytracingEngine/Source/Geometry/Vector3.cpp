#include <stdexcept>
#include "Vector3.h"

using namespace std;

float readCoordinate(xml_node<>* parent, const string& name)
{
	if (xml_node<>* node = parent->first_node(name.c_str()))
	{
		return strtof(node->value(), nullptr);
	}
	throw runtime_error{ "malformed input, Vector3 has no " + name + " coordinate" };
}

Vector3::Vector3(xml_node<>* node)
{
	if (node == nullptr)
		throw runtime_error{ "malformed input, Vector3 container not found" };
	x = readCoordinate(node, "x");
	y = readCoordinate(node, "y");
	z = readCoordinate(node, "z");
}
