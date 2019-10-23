#pragma once
#include "Geometry\Vector3.h"

class Camera
{
	Vector3f position;
	Vector3f orientation;
public:
	Camera(const xml_node<>* node);
	const Vector3f& getPosition() const { return position; }
	const Vector3f& getOrientation() const { return orientation; }
};

