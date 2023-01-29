#pragma once

#include "math/Point.hpp"
#include "math/Vector.hpp"
#include <catch2/catch_test_macros.hpp>


template<>
struct Catch::StringMaker<Point> {
	static std::string convert(Point const& point) {
		return std::format("Point<{}, {}, {}>", point.x, point.y, point.z);
	}
};

template<>
struct Catch::StringMaker<Vector> {
	static std::string convert(Vector const& vector) {
		return std::format("Vector<{}, {}, {}>", vector.x, vector.y, vector.z);
	}
};

extern bool isClose(float a, float b, float epsilon = 0.0001f);

extern float randomFloat(float min, float max);

extern Point randomPoint(float minValue, float maxValue);
extern Vector randomVector(float minValue, float maxValue);