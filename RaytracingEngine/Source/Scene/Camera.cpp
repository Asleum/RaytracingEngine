#include "Camera.h"
#include <stdexcept>
#include <iostream>

using namespace std;

Camera::Camera(const xml_node<>* node)
{
	if (!node)
		throw runtime_error{ "malformed input, camera node not found" };
	m_position = Vector3f{ node->first_node("position") };
	m_orientation = Vector3f{ node->first_node("orientation") }.normalized();
}

vector<Ray> Camera::getViewportRays(int resolutionX, int resolutionY) const
{
	vector<Ray> pixels;
	pixels.reserve(resolutionX * resolutionY);

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
			pixels.emplace_back(m_position, position + xIncrement * static_cast<float>(x) + yIncrement * static_cast<float>(y));
		}
	}
	return pixels;
}
