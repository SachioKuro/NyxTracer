#pragma once

#include "Point.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Transformation.hpp"

struct Ray {
	Ray(Point origin, Vector direction)
		: origin(origin), direction(direction) {}
	Ray() = default;

	Point origin;
	Vector direction;

	Point position(float t) {
		return origin + direction * t;
	}

	Ray operator*(const Matrix& other) const {
		return Ray(other * origin, other * direction);
	}

	Ray translate(float x, float y, float z) {
		Matrix transformation = Transformation::Translation(x, y, z);
		return Ray(transformation * origin, direction);
	}

	Ray scale(float x, float y, float z) {
		Matrix transformation = Transformation::Scaling(x, y, z);
		return Ray(transformation * origin, transformation * direction);
	}
};