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
		for (xml_node<>* node{ root->first_node() }; node; node = node->next_sibling())
		{
			string name{ node->name() };
			if (name == "camera")
			{
				if (m_pCamera)
					throw runtime_error{ "malformed input file, has multiple cameras" };
				m_pCamera = unique_ptr<Camera>{ new Camera{ node } };
			}
		}
	}
	else
		throw runtime_error{ "malformed input file, no scene node" };
}
