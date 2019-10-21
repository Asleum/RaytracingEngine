#include <iostream>
#include "Scene.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace rapidxml;

Scene::Scene(const string& filename)
{
	file<> xmlFile{ filename.c_str() };
	xml_document<> document;
	document.parse<0>(xmlFile.data());

	if (xml_node<>* root{ document.first_node("scene") })
	{
		for (xml_node<>* attr{ root->first_node() }; attr; attr = attr->next_sibling())
		{
			string name{ attr->name() };
			if (name == "camera")
			{
				if (m_camera)
					throw runtime_error{ "malformed input file, has multiple cameras" };
				m_camera = unique_ptr<Camera>{ new Camera };
			}
		}
	}
	else
		throw runtime_error{ "malformed input file, no scene node" };
}
