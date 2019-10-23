#include <iostream>
#include "Scene.h"
#include "Scene/Shapes/Sphere.h"
#include "Scene/Shapes/Plane.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "lodepng.h"

using namespace rapidxml;

Scene::Scene(const string& filename) : m_inputFilename { filename }
{
	file<> xmlFile{ filename.c_str() };
	xml_document<> document;
	document.parse<0>(xmlFile.data());

	if (xml_node<>* root{ document.first_node("scene") })
	{
		for (xml_node<>* node{ root->first_node() }; node; node = node->next_sibling())
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
		image.push_back(color.getX());
		image.push_back(color.getY());
		image.push_back(color.getZ());
		image.push_back(255);
	}

	if (auto error = lodepng::encode(m_inputFilename + ".png", image, resolutionX, resolutionY))
		throw runtime_error(lodepng_error_text(error));
}

Color Scene::traceRay(const Ray& ray)
{
	IntersectionResult intersection;
	for (auto& shape: m_shapes)
	{
		IntersectionResult result = shape->intersect(ray);
		if (result.intersects && (!intersection.intersects || result.distance < intersection.distance))
		{
			intersection = result;
		}
	}
	if (!intersection.intersects)
		return Color{ 0, 0, 0 };
	return Color{0, 255, 0};
}
