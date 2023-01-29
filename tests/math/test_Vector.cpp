#include <catch2/catch_test_macros.hpp>
#include <ctime>
#include <limits>

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

	SECTION("isEqual") {
		SECTION("if coordinate values are the same it is equal (different objects)") {
			float x = randomFloat(-100, 100);
			float y = randomFloat(-100, 100);
			float z = randomFloat(-100, 100);
			Vector v1(x, y, z);
			Vector v2(x, y, z);

			REQUIRE(v1 == v2);
		}

		SECTION("if coordinate values are the same it is equal (same objects)") {
			float x = randomFloat(-100, 100);
			float y = randomFloat(-100, 100);
			float z = randomFloat(-100, 100);
			Vector v1(x, y, z);
			Vector v2 = v1;

			REQUIRE(v1 == v2);
		}

		SECTION("if coordinate values are different it is not equal") {
			float x1 = randomFloat(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
			float y1 = randomFloat(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
			float z1 = randomFloat(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
			Vector v1(x1, y1, z1);


			float x2 = randomFloat(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
			float y2 = randomFloat(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
			float z2 = randomFloat(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
			Vector v2(x2, y2, z2);

			REQUIRE(v1 != v2);
		}
	}
}