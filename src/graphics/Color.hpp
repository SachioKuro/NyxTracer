#pragma once

#include <algorithm>

#include "Constants.hpp"

struct Color  {
	
	Color() : r(0), g(0), b(0), a(1) { }
	Color(float r, float g, float b, float a = 1) : r(r), g(g), b(b), a(a) { }
	
	float r, g, b, a;

	bool operator==(const Color& other) const {
		return abs(r - other.r) < EPSILON &&
			   abs(g - other.g) < EPSILON &&
			   abs(b - other.b) < EPSILON &&
			   abs(a - other.a) < EPSILON;
	}

	bool operator!=(const Color& other) const {
		return !(*this == other);
	}

	Color operator+(const Color& other) const {
		return Color(r + other.r, g + other.g, b + other.b, std::clamp(a + other.a, 0.0f, 1.0f));
	}

	Color operator-(const Color& other) const {
		return Color(r - other.r, g - other.g, b - other.b);
	}

	Color operator*(float scalar) const {
		return Color(r * scalar, g * scalar, b * scalar);
	}

	Color operator*(const Color& other) const {
		return Color(r * other.r, g * other.g, b * other.b);
	}

	Color operator/(float scalar) const {
		return Color(r / scalar, g / scalar, b / scalar);
	}

	Color operator/(const Color& other) const {
		return Color(r / other.r, g / other.g, b / other.b);
	}
};