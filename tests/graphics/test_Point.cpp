#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <ctime>
#include <limits>
#include <tuple>

#include "utils/Util.hpp"
#include "graphics/Point.hpp"


TEST_CASE("Point") {
	srand((unsigned)time(0));
	
	SECTION("Initialize") {
		SECTION("tuple with w=1.0 is a point") {
			float x = randomFloat(-100, 100);
			float y = randomFloat(-100, 100);
			float z = randomFloat(-100, 100);
			Point p(x, y, z);

			CAPTURE(p.w);
			
			REQUIRE(isClose(p.x, x));
			REQUIRE(isClose(p.y, y));
			REQUIRE(isClose(p.z, z));
			REQUIRE(isClose(p.w, 1.0));
		}
	}

	SECTION("isEqual") {
		SECTION("if coordinate values are the same it is equal (different objects)") {
			float x = randomFloat(-100, 100);
			float y = randomFloat(-100, 100);
			float z = randomFloat(-100, 100);
			Point p1(x, y, z);
			Point p2(x, y, z);
			
			REQUIRE(p1 == p2);
		}

		SECTION("if coordinate values are the same it is equal (same objects)") {
			float x = randomFloat(-100, 100);
			float y = randomFloat(-100, 100);
			float z = randomFloat(-100, 100);
			Point p1(x, y, z);
			Point p2 = p1;
			
			REQUIRE(p1 == p2);
		}

		SECTION("if coordinate values are different it is not equal") {
			float x1 = randomFloat(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
			float y1 = randomFloat(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
			float z1 = randomFloat(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
			Point p1(x1, y1, z1);


			float x2 = randomFloat(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
			float y2 = randomFloat(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
			float z2 = randomFloat(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
			Point p2(x2, y2, z2);
			
			REQUIRE(p1 != p2);
		}
	}
	
	SECTION("Addition") {
		SECTION("adding a vector to a point should produce another point") {
			REQUIRE(hasAddtionOperator<Point, Vector>::value);
			
			auto p = GENERATE(
				table<std::tuple<Point, Vector>, Point>({
					{{Point( 0, 0, 0), Vector(4, 5, 6)}, Point( 4, 5, 6)},
					{{Point( 1, 1, 1), Vector(4, 5, 6)}, Point( 5, 6, 7)},
					{{Point( 1, 2, 3), Vector(4, 5, 6)}, Point( 5, 7, 9)},
					{{Point( 1, 2, 3), Vector(1, 1, 1)}, Point( 2, 3, 4)},
					{{Point(-1,-2,-3), Vector(4, 5, 6)}, Point( 3, 3, 3)},
					{{Point(-3,-2,-1), Vector(1, 2, 3)}, Point(-2, 0, 2)},
					{{Point(-4, 1,-2), Vector(0, 0, 0)}, Point(-4, 1,-2)}
				})
			);

			CAPTURE(std::get<0>(std::get<0>(p)));
			CAPTURE(std::get<1>(std::get<0>(p)));
			CAPTURE(std::get<1>(p));
			
			REQUIRE(std::get<0>(std::get<0>(p)) + std::get<1>(std::get<0>(p)) == std::get<1>(p));
		}

		SECTION("adding a point to a vector should not be possible") {
			REQUIRE(!hasAddtionOperator<Vector, Point>::value);
		}

		SECTION("adding 2 points should not be possible") {
			REQUIRE(!hasAddtionOperator<Point, Point>::value);
		}
	}

	SECTION("Substraction") {
		SECTION("substracting a vector from a point should produce another point") {
			REQUIRE(hasSubstractionOperator<Point, Vector>::value);

			auto p = GENERATE(
				table<std::tuple<Point, Vector>, Point>({
					{{Point(0, 0, 0), Vector(4, 5, 6)}, Point(-4, -5, -6)},
					{{Point(1, 1, 1), Vector(4, 5, 6)}, Point(-3, -4, -5)},
					{{Point(1, 2, 3), Vector(4, 5, 6)}, Point(-3, -3, -3)},
					{{Point(1, 2, 3), Vector(1, 1, 1)}, Point(0, 1, 2)},
					{{Point(-1,-2,-3), Vector(4, 5, 6)}, Point(-5, -7, -9)},
					{{Point(-3,-2,-1), Vector(1, 2, 3)}, Point(-4, -4, -4)},
					{{Point(-4, 1,-2), Vector(0, 0, 0)}, Point(-4, 1,-2)}
					})
			);

			CAPTURE(std::get<0>(std::get<0>(p)));
			CAPTURE(std::get<1>(std::get<0>(p)));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(std::get<0>(p)) - std::get<1>(std::get<0>(p)) == std::get<1>(p));
		}

		SECTION("substracting a point from a vector should not be possible") {
			REQUIRE(!hasSubstractionOperator<Vector, Point>::value);
		}

		SECTION("substracting 2 points should produce another vector") {
			REQUIRE(hasSubstractionOperator<Point, Point>::value);

			auto p = GENERATE(
				table<std::tuple<Point, Point>, Vector>({
					{{Point(0, 0, 0), Point(4, 5, 6)}, Vector(-4, -5, -6)},
					{{Point(1, 1, 1), Point(4, 5, 6)}, Vector(-3, -4, -5)},
					{{Point(1, 2, 3), Point(4, 5, 6)}, Vector(-3, -3, -3)},
					{{Point(1, 2, 3), Point(1, 1, 1)}, Vector(0, 1, 2)},
					{{Point(-1,-2,-3), Point(4, 5, 6)}, Vector(-5, -7, -9)},
					{{Point(-3,-2,-1), Point(1, 2, 3)}, Vector(-4, -4, -4)},
					{{Point(-4, 1,-2), Point(0, 0, 0)}, Vector(-4, 1,-2)}
					})
			);

			CAPTURE(std::get<0>(std::get<0>(p)));
			CAPTURE(std::get<1>(std::get<0>(p)));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(std::get<0>(p)) - std::get<1>(std::get<0>(p)) == std::get<1>(p));
		}
	}
}