#include <iostream>
#include "Scene.h"
#include "Scene/Shapes/Sphere.h"
#include "Scene/Shapes/Plane.h"
#include "Utils/xmlUtils.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "lodepng.h"

using namespace rapidxml;

const float EPSILON{ .0001f };
const Color BACKGROUND_COLOR{ .05f, .05f, .05f };
const Color HIGHLIGHT_COLOR{ 1.f, 1.f, 1.f };
const int HIGHLIGHT_EXPONENT{ 5 };
const int MAX_BOUNCES{ 3 };

Scene::Scene(const string& filename) : m_inputFilename { filename }
{
	file<> xmlFile{ filename.c_str() };
	xml_document<> document;
	document.parse<0>(xmlFile.data());

	if (xml_node<>* materials = document.first_node("materials"))
	{
		for (xml_node<>* node = materials->first_node(); node; node = node->next_sibling())
		{
			if (string{ node->name() } == "material")
			{
				string name = readValue<string>(node->first_node("name"));
				m_materials[name] = Material{ node };
			}
		}
	}

	if (xml_node<>* root = document.first_node("scene"))
	{
		for (xml_node<>* node = root->first_node(); node; node = node->next_sibling())
		{
			string name{ node->name() };
			if (name == "camera")
			{
				if (m_pCamera)
					throw runtime_error{ "malformed input file, has multiple cameras" };
				m_pCamera = make_unique<Camera>(node);
			}
			else if (name == "sphere")
			{
				m_shapes.push_back(make_unique<Sphere>(node));
			}
			else if (name == "plane")
			{
				m_shapes.push_back(make_unique<Plane>(node));
			}
			else if (name == "pointLight")
			{
				m_lights.emplace_back(node);
			}
		}
	}
	else
		throw runtime_error{ "malformed input file, no scene node" };
}

void Scene::makeImage(int resolutionX, int resolutionY)
{
	vector<unsigned char> image;
	image.reserve(resolutionX * resolutionY * 4);
	for (Ray& ray : m_pCamera->getViewportRays(resolutionX, resolutionY))
	{
		Color color = traceRay(ray);
		image.push_back(static_cast<unsigned char>(color.getX() * 255));
		image.push_back(static_cast<unsigned char>(color.getY() * 255));
		image.push_back(static_cast<unsigned char>(color.getZ() * 255));
		image.push_back(255);
	}

	if (auto error = lodepng::encode(m_inputFilename + ".png", image, resolutionX, resolutionY))
		throw runtime_error(lodepng_error_text(error));
}

IntersectionResult Scene::getClosestIntersection(const Ray& ray)
{
	IntersectionResult intersection;
	for (auto& shape : m_shapes)
	{
		IntersectionResult result = shape->intersect(ray);
		if (result.intersects && (!intersection.intersects || result.distance < intersection.distance))
		{
			intersection = result;
		}
	}
	return intersection;
}

Color Scene::traceRay(const Ray& ray, int bounces)
{
	IntersectionResult intersection = getClosestIntersection(ray);
	if (!intersection.intersects)
		return BACKGROUND_COLOR;

	Vector3f absNormal = intersection.inside ? -intersection.surfaceNormal : intersection.surfaceNormal;
	Vector3f offsetIntersection = intersection.position + absNormal * EPSILON; // Offset needed to avoid hitting intersected shape again
	const Material& material = m_materials[intersection.materialName];

	Color lightColor;
	float highlightIntensity{ .0f };
	for (const PointLight& light : m_lights)
	{
		Ray shadowRay{ offsetIntersection, light.getPosition()};
		float lightDistance = (light.getPosition() - offsetIntersection).length();

		IntersectionResult shadowIntersection = getClosestIntersection(shadowRay);
		if (!shadowIntersection.intersects || shadowIntersection.distance > lightDistance)
		{
			lightColor += light.getColor() * max(.0f, shadowRay.getDirection().dot(absNormal));
			Vector3f reflected = shadowRay.getDirection().reflected(absNormal);
			highlightIntensity += pow(reflected.dot(-ray.getDirection()), HIGHLIGHT_EXPONENT);
		}
	}
	Color mainColor = (lightColor.clamped(0, 1) * material.getColor() + HIGHLIGHT_COLOR * highlightIntensity).clamped(0, 1);

	if (material.getReflectance() > 0 && bounces < MAX_BOUNCES)
	{
		Ray reflectedRay{ offsetIntersection, offsetIntersection + (-ray.getDirection()).reflected(absNormal) };
		Color reflectedColor = traceRay(reflectedRay, bounces + 1);
		return mainColor * (1 - material.getReflectance()) + reflectedColor * material.getReflectance();
	}

	if (material.getTransparency() > 0 && bounces < MAX_BOUNCES)
	{
		Vector3f insetIntersection = intersection.position - absNormal * EPSILON;
		float n1 = intersection.inside ? material.getRefracionIndex() : 1.f;
		float n2 = intersection.inside ? 1.f : material.getRefracionIndex();
		float reflectionRate = ray.getDirection().reflectionRate(absNormal, n1, n2);
		Ray reflectedRay{ offsetIntersection, offsetIntersection + (-ray.getDirection()).reflected(absNormal) };
		Color reflectedColor = traceRay(reflectedRay, bounces + 1);
		if (reflectionRate < 1)
		{
			Vector3f refractedDirection = ray.getDirection().refracted(absNormal, n1, n2);
			Ray refractedRay{ insetIntersection, insetIntersection + refractedDirection };
			Color refractedColor = traceRay(refractedRay, bounces + 1);
			Color resultColor = refractedColor * (1 - reflectionRate) + reflectedColor * reflectionRate;
			return mainColor * (1 - material.getTransparency()) + resultColor * material.getTransparency();
		}
		return mainColor * (1 - material.getTransparency()) + reflectedColor * material.getTransparency();
	}

	return mainColor;
}
