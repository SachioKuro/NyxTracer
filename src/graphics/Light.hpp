#pragma once

#include "Point.hpp"
#include "Color.hpp"

struct PointLight {
	PointLight(Point position, Color intensity) : position(position), intensity(intensity) {}

	Point position;
	Color intensity;
};