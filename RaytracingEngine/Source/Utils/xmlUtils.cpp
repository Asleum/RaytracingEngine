#include <stdexcept>
#include "xmlUtils.h"

using namespace std;

float readFloat(const xml_node<>* node)
{
	if (!node)
		throw runtime_error{ "malformed input, attempt to read float from inexisting node" };
	return strtof(node->value(), nullptr);
}
