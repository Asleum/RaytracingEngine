#pragma once
#include "Geometry\Vector3.h"

class Camera
{
	Vector3 position;
	Vector3 orientation;
public:
	Camera(xml_node<>* node);
	const Vector3& getPosition() const { return position; }
	const Vector3& getOrientation() const { return orientation; }
};

