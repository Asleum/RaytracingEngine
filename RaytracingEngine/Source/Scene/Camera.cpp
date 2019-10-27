#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>
#include <iostream>
#include "Camera.h"

using namespace std;

Camera::Camera(const xml_node<>* node)
{
	if (!node)
		throw runtime_error{ "malformed input, camera node not found" };
	m_fieldOfView = readValue<float>(node->first_node("fieldOfView")) * M_PI / 180;
	m_position = Vector3f{ node->first_node("position") };
	m_orientation = Vector3f{ node->first_node("orientation") }.normalized();
}

void Camera::calculateViewportRays(int resolutionX, int resolutionY)
{
	m_viewportRays.clear();
	m_viewportRays.reserve(resolutionX * resolutionY);

	Vector3f xDirection = m_orientation.cross(Vector3f{ 0, 0, 1 }).normalized();
	Vector3f yDirection = m_orientation.cross(xDirection).normalized();
	float viewportWidth = 2 * tan(m_fieldOfView);
	float viewportHeight = (viewportWidth * resolutionY) / resolutionX;
	Vector3f position = m_position + m_orientation - xDirection * (viewportWidth / 2) - yDirection * (viewportHeight / 2);
	Vector3f xIncrement = xDirection * (viewportWidth / (resolutionX - 1));
	Vector3f yIncrement = yDirection * (viewportHeight / (resolutionY - 1));
	for (int y = 0; y != resolutionY; ++y)
	{
		for (int x = 0; x != resolutionX; ++x)
		{
			m_viewportRays.emplace_back(m_position, position + xIncrement * static_cast<float>(x) + yIncrement * static_cast<float>(y));
		}
	}
}

const Ray& Camera::getViewportRay(int index) const
{
	assert(index >= 0 && index < m_viewportRays.size());
	return m_viewportRays[index];
}