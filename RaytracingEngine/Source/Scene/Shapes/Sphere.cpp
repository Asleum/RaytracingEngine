#include <stdexcept>
#include "Sphere.h"
#include "Utils/xmlUtils.h"

using namespace std;

Sphere::Sphere(const xml_node<>* node)
{
	if (!node)
		throw runtime_error{ "malformed input, sphere node not found" };
	radius = readValue<float>(node->first_node("radius"));
	position = Vector3f{ node->first_node("position") };
}
