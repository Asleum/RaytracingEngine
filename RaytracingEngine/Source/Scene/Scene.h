#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Camera.h"
#include "Scene/AbstractShape.h"
#include "Scene/PointLight.h"
#include "Geometry/Ray.h"
#include "Materials/Material.h"

using namespace std;

class Scene
{
	const string m_inputFilename;
	unique_ptr<Camera> m_pCamera;
	vector<unique_ptr<AbstractShape>> m_shapes;
	vector<PointLight> m_lights;
	vector<Color> m_image;
	unordered_map<string, Material> m_materials;
	int m_renderResolutionX;
	int m_renderResolutionY;

	IntersectionResult getClosestIntersection(const Ray& ray);
	Color traceRay(const Ray& ray, int bounces = 0);
public:
	Scene(const string& filename);
	const unique_ptr<Camera>& getCamera() const { return m_pCamera; }
	void prepareRendering(int resolutionX, int resolutionY);
	void renderPixel(int pixelIndex);
	void renderAll();
	string finalizeRendering();
};

