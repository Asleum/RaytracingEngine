#pragma once
#include <stdexcept>
#include "rapidxml.hpp"
#include "Utils/xmlUtils.h"


using namespace std;
using namespace rapidxml;

template<typename T>
class Vector3
{
 	T x, y, z;
public:
	Vector3(xml_node<>* node);
	Vector3() : x{}, y{}, z{} {}
	Vector3(T x, T y, T z) : x{ x }, y{ y }, z{ z } {}
	T getX() const { return x; }
	T getY() const { return y; }
	T getZ() const { return z; }
};

using Vector3f = Vector3<float>;

template<typename T>
inline Vector3<T>::Vector3(xml_node<>* node)
{
	if (!node)
		throw runtime_error{ "malformed input, Vector3 container not found" };
	x = readValue<T>(node->first_node("x"));
	y = readValue<T>(node->first_node("y"));
	z = readValue<T>(node->first_node("z"));
}
