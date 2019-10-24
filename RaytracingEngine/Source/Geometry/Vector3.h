#pragma once
#include <cmath>
#include <algorithm>
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
	Vector3(xml_node<>* node, const string& coord1 = "x", const string& coord2 = "y", const string& coord3 = "z");
	Vector3() : x{}, y{}, z{} {}
	Vector3(T x, T y, T z) : x{ x }, y{ y }, z{ z } {}

	T getX() const { return x; }
	T getY() const { return y; }
	T getZ() const { return z; }

	Vector3<T> operator*(T scalar) const { return Vector3<T>{ x * scalar, y * scalar, z * scalar }; }
	Vector3<T> operator/(T scalar) const { return Vector3<T>{ x / scalar, y / scalar, z / scalar }; }
	Vector3<T> operator*(const Vector3<T>& other) const { return Vector3<T>{ x * other.x, y * other.y, z * other.z }; }
	Vector3<T> operator+(const Vector3<T>& other) const { return Vector3<T>{ x + other.x, y + other.y, z + other.z }; }
	Vector3<T> operator-(const Vector3<T>& other) const { return Vector3<T>{ x - other.x, y - other.y, z - other.z }; }
	Vector3<T> operator-() const { return Vector3<T>{ -x, -y, -z }; }
	Vector3<T>& operator+=(const Vector3<T>& other)
	{
		x += other.getX();
		y += other.getY();
		z += other.getZ();
		return *this;
	}

	T length() const { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }
	Vector3<T> normalized() { return *this / length(); }
	T dot(const Vector3<T>& other) const { return x * other.x + y * other.y + z * other.z; }
	Vector3<T> cross(const Vector3<T>& other) const
	{
		return Vector3{ y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
	}
	Vector3<T> clamped(T smallest, T biggest) const 
	{ 
		return Vector3{ max(min(x, biggest), smallest), max(min(y, biggest), smallest) , max(min(z, biggest), smallest) };
	}
	Vector3<T> reflected(const Vector3<T>& normal) const
	{
		return normal * (2 * normal.dot(*this)) - *this;
	}
};

using Vector3f = Vector3<float>;
using Color = Vector3<float>;

template<typename T>
inline Vector3<T>::Vector3(xml_node<>* node, const string& coord1, const string& coord2, const string& coord3)
{
	if (!node)
		throw runtime_error{ "malformed input, Vector3 container not found" };
	x = readValue<T>(node->first_node(coord1.c_str()));
	y = readValue<T>(node->first_node(coord2.c_str()));
	z = readValue<T>(node->first_node(coord3.c_str()));
}

template<typename T>
ostream& operator<<(ostream& stream, const Vector3<T>& vector)
{
	return stream << "(" << vector.getX() << "; " << vector.getY() << "; " << vector.getZ() << ")";
}