#pragma once
#include <string>
#include "Camera.h"

using namespace std;

class Scene
{
	unique_ptr<Camera> m_camera;
public:
	Scene(const string& filename);
	Scene() {};
};

