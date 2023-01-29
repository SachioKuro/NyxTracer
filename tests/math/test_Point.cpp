#include <catch2/catch_test_macros.hpp>

#include "utils/Util.hpp"

#include "math/Point.hpp"

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
}