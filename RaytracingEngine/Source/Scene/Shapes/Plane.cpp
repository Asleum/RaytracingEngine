#include <stdexcept>
#include <iostream>
#include "Plane.h"

using namespace std;


Plane::Plane(const xml_node<>* node) : AbstractShape(node)
{
	m_position = Vector3f{ node->first_node("position") };
	m_normal = Vector3f{ node->first_node("normal") }.normalized();
}

IntersectionResult Plane::intersect(const Ray& ray) const
{
	IntersectionResult result;
	float t = (m_position - ray.getOrigin()).dot(m_normal) / ray.getDirection().dot(m_normal);
	if (t < 0)
		return result;

	result.intersects = true;
	result.distance = t;
	result.position = ray.getOrigin() + ray.getDirection() * t;
	result.surfaceNormal = m_normal.dot(ray.getDirection()) > 0 ? -m_normal : m_normal;
	result.materialName = m_materialName;
	result.inside = false;
	return result;
}
