#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Camera.h"
#include "Scene/AbstractShape.h"
#include "Geometry/Ray.h"

using namespace std;

class Scene
{
	const string m_inputFilename;
	unique_ptr<Camera> m_pCamera;
	vector<unique_ptr<AbstractShape>> m_shapes;

	Color traceRay(const Ray& ray);
public:
	Scene(const string& filename);
	const unique_ptr<Camera>& getCamera() const { return m_pCamera; }
	void makeImage(int resolutionX, int resolutionY);
};

