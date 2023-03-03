#pragma once

#include <catch2/catch_test_macros.hpp>
#include <numeric>

#include "graphics/Color.hpp"
#include "graphics/Point.hpp"
#include "graphics/Vector.hpp"
#include "graphics/Matrix.hpp"
#include "graphics/Ray.hpp"
#include "graphics/Sphere.hpp"


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

template<>
struct Catch::StringMaker<Color> {
	static std::string convert(Color const& color) {
		return std::format("Color<{}, {}, {}, {}>", color.r, color.g, color.b, color.a);
	}
};

template<>
struct Catch::StringMaker<Ray> {
	static std::string convert(Ray const& ray) {
		return std::format("Ray<{}, {}>",
			Catch::StringMaker<Point>::convert(ray.origin), Catch::StringMaker<Vector>::convert(ray.direction));
	}
};

template<>
struct Catch::StringMaker<Sphere> {
	static std::string convert(Sphere const& sphere) {
		return "Sphere<>";
	}
};

template<>
struct Catch::StringMaker<Intersection> {
	static std::string convert(Intersection const& intersection) {
		return std::format("Intersection<{}, {}>", intersection.t, intersection.obj);
	}
};

template<>
struct Catch::StringMaker<Intersections> {
	static std::string convert(Intersections const& intersections) {
		auto data = intersections.data;
		if (data.size() > 0)
			return std::format("Intersections<{}>", std::accumulate(data.begin() + 1, data.end(), Catch::StringMaker<Intersection>::convert(data[0]),
				[](const std::string& a, Intersection b) { return a + ", " + Catch::StringMaker<Intersection>::convert(b); }));
		else {
			return "Intersections<>";
		}
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
extern bool isClose(Point a, Point b, float epsilon = 0.0001f);
extern bool isClose(Vector a, Vector b, float epsilon = 0.0001f);
extern bool isClose(Matrix a, Matrix b, float epsilon = 0.0001f);

extern float randomFloat(float min = -1000000, float max = 1000000);
extern float randomInt(int min = -1000000, int max = 1000000);

extern Point randomPoint(float minValue = -100, float maxValue = 100);
extern Vector randomVector(float minValue = -100, float maxValue = 100);
extern Matrix randomMatrix4x4(float minValue = -100, float maxValue = 100);
