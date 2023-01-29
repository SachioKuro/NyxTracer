#include <catch2/catch_test_macros.hpp>

#include "utils/Util.hpp"

#include "math/Vector.hpp"

TEST_CASE("Vector") {
	srand((unsigned)time(0));

	SECTION("Initialize") {
		SECTION("tuple with w=1.0 is a vector") {
			float x = randomFloat(-100, 100);
			float y = randomFloat(-100, 100);
			float z = randomFloat(-100, 100);
			Vector v(x, y, z);

			CAPTURE(v.w);

			REQUIRE(isClose(v.x, x));
			REQUIRE(isClose(v.y, y));
			REQUIRE(isClose(v.z, z));
			REQUIRE(isClose(v.w, 0.0));
		}
	}
}