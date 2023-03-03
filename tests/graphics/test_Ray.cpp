#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <ctime>
#include <limits>
#include <tuple>

#include "utils/Util.hpp"
#include "graphics/Ray.hpp"
#include "graphics/Vector.hpp"
#include "graphics/Point.hpp"


TEST_CASE("Ray") {
	srand((unsigned)time(0));

	SECTION("Initialize") {
		Point origin(1, 2, 3);
		Vector direction(4, 5, 6);
		Ray r(origin, direction);

		REQUIRE(r.origin == origin);
		REQUIRE(r.direction == direction);
	}

	SECTION("Position") {
		SECTION("Single direction") {
			Point origin(2, 3, 4);
			Vector direction(1, 0, 0);
			Ray r(origin, direction);

			auto p = GENERATE(
				table<float, Point>({
					{0, Point(2, 3, 4)},
					{1, Point(3, 3, 4)},
					{-1, Point(1, 3, 4)},
					{2.5, Point(4.5, 3, 4)}
					})
			);

			CAPTURE(std::get<0>(p));
			CAPTURE(std::get<1>(p));

			REQUIRE(r.position(std::get<0>(p)) == std::get<1>(p));
		}

		SECTION("Multiple directions") {
			Point origin(4, 4, 4);
			Vector direction(0, 1, 0.5);
			Ray r(origin, direction);

			auto p = GENERATE(
				table<float, Point>({
					{0, Point(4, 4, 4)},
					{1, Point(4, 5, 4.5)},
					{-1, Point(4, 3, 3.5)},
					{2.5, Point(4, 6.5, 5.25)}
				})
			);

			CAPTURE(std::get<0>(p));
			CAPTURE(std::get<1>(p));

			REQUIRE(r.position(std::get<0>(p)) == std::get<1>(p));
		}
	}

	SECTION("Transformation") {
		SECTION("Translation") {
			Point origin(4, 4, 4);
			Vector direction(0, 1, 0.5);
			Ray r(origin, direction);

			Ray rTrans = r.translate(3, 4, 5);

			REQUIRE(rTrans.origin == Transformation::Translation(3, 4, 5) * origin);
			REQUIRE(rTrans.direction == direction);
		}

		SECTION("Scaling") {
			Point origin(4, 4, 4);
			Vector direction(0, 1, 0.5);
			Ray r(origin, direction);

			Ray rTrans = r.scale(3, 4, 5);

			REQUIRE(rTrans.origin == Transformation::Scaling(3, 4, 5) * origin);
			REQUIRE(rTrans.direction == Transformation::Scaling(3, 4, 5) * direction);
		}
	}
}