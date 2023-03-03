#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <ctime>
#include <limits>
#include <tuple>
#include <vector>

#include "utils/Util.hpp"
#include "graphics/Intersections.hpp"
#include "graphics/Sphere.hpp"
#include "graphics/Ray.hpp"
#include "graphics/Vector.hpp"
#include "graphics/Point.hpp"

TEST_CASE("Intersections") {
	srand((unsigned)time(0));

	SECTION("Intersect") {
		SECTION("Circle") {
			SECTION("through center") {
				auto p = GENERATE(
					table<std::tuple<Sphere, Ray>, Intersections>({
						{{Sphere(), Ray(Point(0, 0, -5), Vector(0, 0, 1))}, Intersections(std::vector{Intersection(4.0f, 0), Intersection(6.0f, 0)})},
						{{Sphere(), Ray(Point(0, 0, 0), Vector(0, 0, 1))}, Intersections(std::vector{Intersection(-1.0f, 0), Intersection(1.0f, 0)})},
						{{Sphere(), Ray(Point(0, 0, 5), Vector(0, 0, 1))}, Intersections(std::vector{Intersection(-6.0f, 0), Intersection(-4.0f, 0)})},
					})
				);

				CAPTURE(std::get<0>(std::get<0>(p)));
				CAPTURE(std::get<1>(std::get<0>(p)));
				CAPTURE(std::get<1>(p));

				REQUIRE(std::get<0>(std::get<0>(p)).intersect(std::get<1>(std::get<0>(p))) == std::get<1>(p));
			}

			SECTION("tangent intersection") {
				auto p = GENERATE(
					table<std::tuple<Sphere, Ray>, Intersections>({
						{{Sphere(), Ray(Point(0, 1, -5), Vector(0, 0, 1))}, Intersections(std::vector{Intersection(5.0f, 0), Intersection(5.0f, 0)})},
					})
				);

				CAPTURE(std::get<0>(std::get<0>(p)));
				CAPTURE(std::get<1>(std::get<0>(p)));
				CAPTURE(std::get<1>(p));

				REQUIRE(std::get<0>(std::get<0>(p)).intersect(std::get<1>(std::get<0>(p))) == std::get<1>(p));
			}

			SECTION("no intersection") {
				auto p = GENERATE(
					table<std::tuple<Sphere, Ray>, Intersections>({
						{{Sphere(), Ray(Point(0, 2, -5), Vector(0, 0, 1))}, Intersections(std::vector<Intersection>{})}
					})
				);

				CAPTURE(std::get<0>(std::get<0>(p)));
				CAPTURE(std::get<1>(std::get<0>(p)));
				CAPTURE(std::get<1>(p));

				REQUIRE(std::get<0>(std::get<0>(p)).intersect(std::get<1>(std::get<0>(p))) == std::get<1>(p));
			}

			SECTION("scaled Sphere") {
				auto p = GENERATE(
					table<std::tuple<Sphere, Ray, Matrix>, Intersections>({
						{
							{Sphere(), Ray(Point(0, 0, -5), Vector(0, 0, 1)), Transformation::Scaling(2, 2, 2)},
							Intersections(std::vector{Intersection(3.0f, 0), Intersection(7.0f, 0)})
						}
					})
				);

				std::get<0>(std::get<0>(p)).transform = std::get<2>(std::get<0>(p));

				CAPTURE(std::get<0>(std::get<0>(p)));
				CAPTURE(std::get<1>(std::get<0>(p)));
				CAPTURE(std::get<2>(std::get<0>(p)));
				CAPTURE(std::get<1>(p));

				REQUIRE(std::get<0>(std::get<0>(p)).intersect(std::get<1>(std::get<0>(p))) == std::get<1>(p));
			}

			SECTION("translated Sphere") {
				auto p = GENERATE(
					table<std::tuple<Sphere, Ray, Matrix>, Intersections>({
						{
							{Sphere(), Ray(Point(0, 0, -5), Vector(0, 0, 1)), Transformation::Translation(5, 0, 0)},
							Intersections(std::vector<Intersection>{})
						}
					})
				);

				std::get<0>(std::get<0>(p)).transform = std::get<2>(std::get<0>(p));

				CAPTURE(std::get<0>(std::get<0>(p)));
				CAPTURE(std::get<1>(std::get<0>(p)));
				CAPTURE(std::get<2>(std::get<0>(p)));
				CAPTURE(std::get<1>(p));

				REQUIRE(std::get<0>(std::get<0>(p)).intersect(std::get<1>(std::get<0>(p))) == std::get<1>(p));
			}
		}
	}

	SECTION("Hit") {
		SECTION("all positive t") {
			auto p = GENERATE(
				table<Intersections, Intersection>({
					{Intersections(std::vector{Intersection(5.0f, 0), Intersection(5.0f, 0)}), Intersection(5.0f, 0)},
					{Intersections(std::vector{Intersection(2.0f, 0), Intersection(3.0f, 0)}), Intersection(2.0f, 0)},
				})
			);

			CAPTURE(std::get<0>(p));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(p).hit() == std::get<1>(p));
		}

		SECTION("with negative t") {
			auto p = GENERATE(
				table<Intersections, Intersection>({
					{Intersections(std::vector{Intersection(-1.0f, 0), Intersection(4.0f, 0)}), Intersection(4.0f, 0)},
					{Intersections(std::vector{Intersection(-2.0f, 0), Intersection(3.0f, 0), Intersection(5.0f, 0)}), Intersection(3.0f, 0)},
				})
			);

			CAPTURE(std::get<0>(p));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(p).hit() == std::get<1>(p));
		}

		SECTION("all negative t") {
			auto p = GENERATE(
				table<Intersections, std::optional<Intersection>>({
					{Intersections(std::vector{Intersection(-4.0f, 0), Intersection(-2.0f, 0)}), std::nullopt},
					{Intersections(std::vector{Intersection(-3.0f, 0), Intersection(-1.0f, 0)}), std::nullopt},
				})
			);

			CAPTURE(std::get<0>(p));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(p).hit() == std::get<1>(p));
		}

		SECTION("no t") {
			auto p = GENERATE(
				table<Intersections, std::optional<Intersection>>({
					{Intersections(std::vector<Intersection>{}), std::nullopt},
					{Intersections(std::vector<Intersection>{}), std::nullopt},
				})
			);

			CAPTURE(std::get<0>(p));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(p).hit() == std::get<1>(p));
		}
	}
}