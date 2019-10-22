#include "Camera.h"
#include <stdexcept>

using namespace std;

Camera::Camera(const xml_node<>* node)
{
	if (!node)
		throw runtime_error{ "malformed input, camera node not found" };
	position = Vector3{ node->first_node("position") };
	orientation = Vector3{ node->first_node("orientation") };
}
