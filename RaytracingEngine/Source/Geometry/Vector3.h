#pragma once
#include <cmath>
#include <stdexcept>
#include "rapidxml.hpp"
#include "Utils/xmlUtils.h"


using namespace std;
using namespace rapidxml;

const float EPSILON{ .0001f };

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

	Vector3<T> operator*(T scalar) const { return Vector3<T>{x * scalar, y * scalar, z * scalar}; }
	Vector3<T> operator/(T scalar) const { return Vector3<T>{x / scalar, y / scalar, z / scalar}; }
	Vector3<T> operator+(const Vector3<T>& other) const { return Vector3<T>{x + other.x, y + other.y, z + other.z }; }
	Vector3<T> operator-(const Vector3<T>& other) const { return Vector3<T>{x - other.x, y - other.y, z - other.z }; }
	bool operator==(const Vector3<T>& other) const { return abs(x - other.x) < EPSILON && abs(y - other.y) < EPSILON && abs(z - other.z) < EPSILON; }

	T length() const { return sqrt(pow(x, 2) + pow(y, 2) + pow(y, 3)); }
	Vector3<T> normalized() { return *this / length(); }
	T dot(const Vector3<T>& other) const { return x * other.x + y * other.y + z * other.z; }
	Vector3<T> cross(const Vector3<T>& other) const {
		return Vector3{ y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
	}
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
