#pragma once

#include <cmath>

#include "Constants.hpp"
#include "Vector.hpp"

struct Point {
	Point(float x, float y, float z) : x(x), y(y), z(z) { }
	
	float x;
	float y;
	float z;
	float w = 1.0f;

	bool operator==(const Point& other) const {
		return abs(x - other.x) < EPSILON && abs(y - other.y) < EPSILON && abs(z - other.z) < EPSILON;
	}
	
	bool operator!=(const Point& other) const {
		return !(*this == other);
	}

	Point operator+(const Vector& other) const {
		return Point(x + other.x, y + other.y, z + other.z);
	}

	Point operator-(const Vector& other) const {
		return Point(x - other.x, y - other.y, z - other.z);
	}

	Vector operator-(const Point& other) const {
		return Vector(x - other.x, y - other.y, z - other.z);
	}
};