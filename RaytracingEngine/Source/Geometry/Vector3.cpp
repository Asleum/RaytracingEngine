#include <stdexcept>
#include "Vector3.h"
#include "Utils/xmlUtils.h"

using namespace std;

Vector3::Vector3(xml_node<>* node)
{
	if (!node)
		throw runtime_error{ "malformed input, Vector3 container not found" };
	x = readFloat(node->first_node("x"));
	y = readFloat(node->first_node("y"));
	z = readFloat(node->first_node("z"));
}
