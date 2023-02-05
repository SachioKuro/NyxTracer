#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <ctime>
#include <limits>
#include <tuple>

#include "utils/Util.hpp"
#include "graphics/Color.hpp"

TEST_CASE("Color") {
	srand((unsigned)time(0));

	SECTION("Initialize") {
		SECTION("tuple with is a color") {
			float r = randomFloat(-100, 100);
			float g = randomFloat(-100, 100);
			float b = randomFloat(-100, 100);
			float a = randomFloat(-100, 100);
			Color c(r, g, b, a);

			CAPTURE(c.r);
			CAPTURE(c.g);
			CAPTURE(c.b);
			CAPTURE(c.a);

			REQUIRE(isClose(c.r, r));
			REQUIRE(isClose(c.g, g));
			REQUIRE(isClose(c.b, b));
			REQUIRE(isClose(c.a, a));
		}

		SECTION("alpha should be default to 1") {
			float r = randomFloat(-100, 100);
			float g = randomFloat(-100, 100);
			float b = randomFloat(-100, 100);
			Color c(r, g, b);

			CAPTURE(c.r);
			CAPTURE(c.g);
			CAPTURE(c.b);
			CAPTURE(c.a);

			REQUIRE(isClose(c.r, r));
			REQUIRE(isClose(c.g, g));
			REQUIRE(isClose(c.b, b));
			REQUIRE(isClose(c.a, 1.0));
		}
	}

	SECTION("Addition") {
		SECTION("adding a color to a color should produce another color") {
			REQUIRE(hasAddtionOperator<Color, Color>::value);

			auto p = GENERATE(
				table<std::tuple<Color, Color>, Color>({
					{{Color(0, 0, 0), Color(.4, .5, .6)}, Color(.4, .5, .6)},
					{{Color(.1, .1, .1), Color(.4, .5, .6)}, Color(.5, .6, .7)},
					{{Color(.1, .2, .3), Color(.4, .5, .6)}, Color(.5, .7, .9)},
					{{Color(.1, .2, .3), Color(.1, .1, .1)}, Color(.2, .3, .4)},
					{{Color(-.1,-.2,-.3), Color(.4, .5, .6)}, Color(.3, .3, .3)},
					{{Color(-.3,-.2,-.1), Color(.1, .2, .3)}, Color(-.2, 0, .2)},
					{{Color(-.4, .1,-.2), Color(0, 0, 0)}, Color(-.4, .1,-.2)},
					{{Color(.4, .1,.2), Color(.7, .1, 1.0)}, Color(1.1, .2, 1.2)},
					{{Color(.4, .1,.2, .5), Color(.7, .1, 1.0, .5)}, Color(1.1, .2 ,1.2)},
					{{Color(.4, .1,.2, .4), Color(.7, .1, 1.0, .2)}, Color(1.1, .2, 1.2, .6)},
					{{Color(.4, .1,.2, .4), Color(.7, .1, 1.0, .8)}, Color(1.1, .2, 1.2)},
				})
			);

			CAPTURE(std::get<0>(std::get<0>(p)));
			CAPTURE(std::get<1>(std::get<0>(p)));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(std::get<0>(p)) + std::get<1>(std::get<0>(p)) == std::get<1>(p));
		}
	}

	SECTION("Substraction") {
		SECTION("substracting a color from a color should produce another color") {
			REQUIRE(hasSubstractionOperator<Point, Vector>::value);

			auto p = GENERATE(
				table<std::tuple<Color, Color>, Color>({
					{{Color(0, 0, 0), Color(.4, .5, .6)}, Color(-.4, -.5, -.6)},
					{{Color(.1, .1, .1), Color(.4, .5, .6)}, Color(-.3, -.4, -.5)},
					{{Color(.1, .2, .3), Color(.4, .5, .6)}, Color(-.3, -.3, -.3)},
					{{Color(.1, .2, .3), Color(.1, .1, .1)}, Color(.0, .1, .2)},
					{{Color(-.1,-.2,-.3), Color(.4, .5, .6)}, Color(-.5, -.7, -.9)},
					{{Color(-.3,-.2,-.1), Color(.1, .2, .3)}, Color(-.4, -.4, -.4)},
					{{Color(-.4, .1,-.2), Color(0, 0, 0)}, Color(-.4, .1, -.2)},
					{{Color(.4, .1,.2), Color(.7, .1, 1.0)}, Color(-.3, .0, -.8)}
				})
			);

			CAPTURE(std::get<0>(std::get<0>(p)));
			CAPTURE(std::get<1>(std::get<0>(p)));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(std::get<0>(p)) - std::get<1>(std::get<0>(p)) == std::get<1>(p));
		}
	}

	SECTION("Scalar-Multiplication") {
		SECTION("multiplying a color with a scalar should produce another color") {
			auto p = GENERATE(
				table<std::tuple<Color, float>, Color>({
					{{Color(.1, .2, .3), 0}, Color(0, 0, 0)},
					{{Color(.1, .2, .3), 1.3}, Color(.13, .26, .39)},
					{{Color(.5, .2, -.3), 2.3}, Color(1.15, .46, -.69)},
					{{Color(.0, .0, .0), 2.3}, Color(.0, .0, .0)},
					{{Color(.4, .8, -.9), -1.3}, Color(-.52, -1.04, 1.17)}
				})
			);

			CAPTURE(std::get<0>(std::get<0>(p)));
			CAPTURE(std::get<1>(std::get<0>(p)));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(std::get<0>(p)) * std::get<1>(std::get<0>(p)) == std::get<1>(p));
		}
	}

	SECTION("Scalar-Division") {
		SECTION("dividing a vector with a scalar should produce another vector on the same direction") {
			auto p = GENERATE(
				table<std::tuple<Color, float>, Color>({
					{{Color(.1, .2, .3), 1.3}, Color(.076923076923076923, .1538461538461538, .2307692307692308)},
					{{Color(.5, .2, -.3), 2.3}, Color(.2173913043478261, .0869565217391304, -.1304347826086957)},
					{{Color(.0, .0, .0), 2.3}, Color(.0, .0, .0)},
					{{Color(.4, .8, -.9), -1.3}, Color(-.3076923076923077, -.6153846153846154, .6923076923076923)},
					{{Color(.4, .8, -.9), .2}, Color(2, 4, -4.5)},
				})
			);

			CAPTURE(std::get<0>(std::get<0>(p)));
			CAPTURE(std::get<1>(std::get<0>(p)));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(std::get<0>(p)) / std::get<1>(std::get<0>(p)) == std::get<1>(p));
		}
	}

	SECTION("Multiplication") {
		SECTION("multiplying a color with a color should produce another color") {
			REQUIRE(hasSubstractionOperator<Point, Vector>::value);

			auto p = GENERATE(
				table<std::tuple<Color, Color>, Color>({
					{{Color(0, 0, 0), Color(.4, .5, .6)}, Color(0, 0, 0)},
					{{Color(.1, .1, .1), Color(.4, .5, .6)}, Color(.04, .05, .06)},
					{{Color(.1, .2, .3), Color(.4, .5, -.6)}, Color(.04, .1, -.18)},
					{{Color(.1, .2, .3), Color(.1, -.1, .1)}, Color(.01, -.02, .03)},
					{{Color(-.1,-.2,-.3), Color(.4, .5, .6)}, Color(-.04, -.1, -.18)},
					{{Color(-.3,-.2,-.1), Color(.1, .2, .3)}, Color(-.03, -.04, -.03)},
					{{Color(-.4, .1,-.2), Color(0, 0, 0)}, Color(0, 0, 0)},
					{{Color(.4, .1,.2), Color(.7, .1, 1.0)}, Color(.28, .01, .2)}
					})
			);

			CAPTURE(std::get<0>(std::get<0>(p)));
			CAPTURE(std::get<1>(std::get<0>(p)));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(std::get<0>(p)) * std::get<1>(std::get<0>(p)) == std::get<1>(p));
		}
	}

	SECTION("Division") {
		SECTION("dividing a color with a color should produce another color") {
			REQUIRE(hasSubstractionOperator<Point, Vector>::value);

			auto p = GENERATE(
				table<std::tuple<Color, Color>, Color>({
					{{Color(0, 0, 0), Color(.4, .5, .6)}, Color(0, 0, 0)},
					{{Color(.1, .1, .1), Color(.4, .5, .6)}, Color(.25, .2, .1666666666666667)},
					{{Color(.1, .2, .3), Color(.4, .5, -.6)}, Color(.25, .4, -.5)},
					{{Color(.1, .2, .3), Color(.1, -.1, .1)}, Color(1, -2, 3)},
					{{Color(-.1,-.2,-.3), Color(.4, .5, .6)}, Color(-.25, -.4, -.5)},
					{{Color(-.3,-.2,-.1), Color(.1, .2, .3)}, Color(-3, -1, -.3333333333333333)},
					{{Color(.4, .1,.2), Color(.7, .1, 1.0)}, Color(.5714285714285714, 1, .2)}
					})
			);

			CAPTURE(std::get<0>(std::get<0>(p)));
			CAPTURE(std::get<1>(std::get<0>(p)));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(std::get<0>(p)) / std::get<1>(std::get<0>(p)) == std::get<1>(p));
		}
	}
}