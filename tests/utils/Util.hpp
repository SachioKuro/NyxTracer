#pragma once

#include <catch2/catch_test_macros.hpp>

#include "math/Point.hpp"
#include "math/Vector.hpp"


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

template <typename T, typename U>
class hasAddtionOperator
{
	template <typename C, typename = decltype(std::declval<C>() + std::declval<U>())>
	static std::true_type test(int) { return std::true_type(); }
	template <typename C>
	static std::false_type test(...) { return std::false_type(); }

public:
	static constexpr bool value = decltype(test<T>(0))::value;
};

template <typename T, typename U>
class hasSubstractionOperator
{
	template <typename C, typename = decltype(std::declval<C>() - std::declval<U>())>
	static std::true_type test(int) { return std::true_type(); }
	template <typename C>
	static std::false_type test(...) { return std::false_type(); }

public:
	static constexpr bool value = decltype(test<T>(0))::value;
};

extern bool isClose(float a, float b, float epsilon = 0.0001f);

extern float randomFloat(float min, float max);

extern Point randomPoint(float minValue = -100, float maxValue = 100);
extern Vector randomVector(float minValue = -100, float maxValue = 100);
