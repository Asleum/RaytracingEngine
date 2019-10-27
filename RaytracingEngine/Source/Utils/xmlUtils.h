#pragma once
#include <stdexcept>
#include <sstream>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;


template<typename T>
T readValue(const xml_node<>* node)
{
	if (!node)
		throw runtime_error{ "malformed input, attempt to read from inexisting node" };
	T value;
	istringstream{ node->value() } >> value;
	return value;
};