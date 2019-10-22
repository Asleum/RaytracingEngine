#pragma once
#include "rapidxml.hpp"

using namespace rapidxml;

class Vector3
{
	float x, y, z;
public:
	Vector3(xml_node<>* node);
	Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {}
	Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}
	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }
};

