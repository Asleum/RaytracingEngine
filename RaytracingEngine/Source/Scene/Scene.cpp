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
	image.resize(resolutionX * resolutionY * 4);
	for (int x = 0; x != resolutionX; ++x)
	{
		for (int y = 0; y != resolutionY; ++y)
		{
			Ray r{ {0, 0, 0}, {0, 0, 0} };
			image[4 * resolutionX * y + 4 * x + 0] = traceRay(r) ? 255 : 0;
			image[4 * resolutionX * y + 4 * x + 1] = 0;
			image[4 * resolutionX * y + 4 * x + 2] = 0;
			image[4 * resolutionX * y + 4 * x + 3] = 255;
		}
	}
	if (!lodepng::encode(m_inputFilename + ".png", image, resolutionX, resolutionY))
		throw runtime_error("error when encoding png image");
}
