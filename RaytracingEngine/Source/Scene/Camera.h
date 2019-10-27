#pragma once
#include <vector>
#include "Geometry/Vector3.h"
#include "Geometry/Ray.h"


class Camera
{
	vector<Ray> m_viewportRays;
	Vector3f m_position;
	Vector3f m_orientation;
	float m_fieldOfView;
public:
	Camera(const xml_node<>* node);
	const Vector3f& getPosition() const { return m_position; }
	const Vector3f& getOrientation() const { return m_orientation; }
	void calculateViewportRays(int resolutionX, int resolutionY);
	const Ray& getViewportRay(int index) const;
};