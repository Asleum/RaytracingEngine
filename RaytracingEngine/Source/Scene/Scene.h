#pragma once
#include <string>
#include "Camera.h"

using namespace std;

class Scene
{
	unique_ptr<Camera> m_pCamera;
public:
	Scene(const string& filename);
	const unique_ptr<Camera>& getCamera() const { return m_pCamera; }
};

