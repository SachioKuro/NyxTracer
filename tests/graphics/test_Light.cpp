#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <ctime>
#include <limits>
#include <tuple>
#include <cmath>

#include "utils/Util.hpp"
#include "graphics/Light.hpp"
#include "graphics/Color.hpp"
#include "graphics/Point.hpp"


TEST_CASE("Light") {
	srand((unsigned)time(0));

	SECTION("Point Light") {
		SECTION("Initialize") {
			Color intensity(1, 1, 1);
			Point position(0, 0, 0);
			PointLight pl(position, intensity);

			REQUIRE(pl.position == position);
			REQUIRE(pl.intensity == intensity);
		}
	}
}