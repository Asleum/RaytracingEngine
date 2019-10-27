#include <stdexcept>
#include <iostream>
#include "Sphere.h"
#include "Utils/xmlUtils.h"

using namespace std;

Sphere::Sphere(const xml_node<>* node) : AbstractShape(node)
{
	m_radius = readValue<float>(node->first_node("radius"));
	m_position = Vector3f{ node->first_node("position") };
}

IntersectionResult Sphere::intersect(const Ray& ray) const
{
	IntersectionResult result;
	float a = ray.getDirection().dot(ray.getDirection());
	float b = ray.getDirection().dot(ray.getOrigin() - m_position) * 2;
	float c = (ray.getOrigin() - m_position).dot(ray.getOrigin() - m_position) - pow(m_radius, 2);
	float delta = pow(b, 2) - 4 * a * c;
	if (delta < 0)
		return result;

	float t1{ (-b - sqrt(delta)) / (2 * a) };
	float t2{ (-b + sqrt(delta)) / (2 * a) };
	if (t1 < 0 && t2 < 0)
		return result;

	result.intersects = true;
	result.distance = (t1 < 0) ? t2 : t1;
	result.position = ray.getOrigin() + ray.getDirection() * result.distance;
	result.surfaceNormal = (result.position - m_position).normalized();
	result.materialName = m_materialName;
	result.inside = t1 < 0;
	return result;
}
