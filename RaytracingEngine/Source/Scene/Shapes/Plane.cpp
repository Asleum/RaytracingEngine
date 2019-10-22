#include <stdexcept>
#include "Plane.h"

using namespace std;

Plane::Plane(const xml_node<>* node)
{
	if (!node)
		throw runtime_error{ "malformed input, plane node not found" };
	position = Vector3{ node->first_node("position") };
	normal = Vector3{ node->first_node("normal") };
}
