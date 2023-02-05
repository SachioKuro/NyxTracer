#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <ctime>
#include <limits>
#include <tuple>

#include "utils/Util.hpp"
#include "graphics/Vector.hpp"

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

	SECTION("Addition") {
		SECTION("adding a vector to a vector should produce another vector") {
			REQUIRE(hasAddtionOperator<Point, Vector>::value);

			auto p = GENERATE(
				table<std::tuple<Vector, Vector>, Vector>({
					{{Vector(0, 0, 0), Vector(4, 5, 6)}, Vector(4, 5, 6)},
					{{Vector(1, 1, 1), Vector(4, 5, 6)}, Vector(5, 6, 7)},
					{{Vector(1, 2, 3), Vector(4, 5, 6)}, Vector(5, 7, 9)},
					{{Vector(1, 2, 3), Vector(1, 1, 1)}, Vector(2, 3, 4)},
					{{Vector(-1,-2,-3), Vector(4, 5, 6)}, Vector(3, 3, 3)},
					{{Vector(-3,-2,-1), Vector(1, 2, 3)}, Vector(-2, 0, 2)},
					{{Vector(-4, 1,-2), Vector(0, 0, 0)}, Vector(-4, 1,-2)}
					})
			);

			CAPTURE(std::get<0>(std::get<0>(p)));
			CAPTURE(std::get<1>(std::get<0>(p)));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(std::get<0>(p)) + std::get<1>(std::get<0>(p)) == std::get<1>(p));
		}
	}

	SECTION("Substraction") {
		SECTION("substracting a vector from a vector should produce another vector") {
			REQUIRE(hasSubstractionOperator<Point, Vector>::value);

			auto p = GENERATE(
				table<std::tuple<Vector, Vector>, Vector>({
					{{Vector(0, 0, 0), Vector(4, 5, 6)}, Vector(-4, -5, -6)},
					{{Vector(1, 1, 1), Vector(4, 5, 6)}, Vector(-3, -4, -5)},
					{{Vector(1, 2, 3), Vector(4, 5, 6)}, Vector(-3, -3, -3)},
					{{Vector(1, 2, 3), Vector(1, 1, 1)}, Vector(0, 1, 2)},
					{{Vector(-1,-2,-3), Vector(4, 5, 6)}, Vector(-5, -7, -9)},
					{{Vector(-3,-2,-1), Vector(1, 2, 3)}, Vector(-4, -4, -4)},
					{{Vector(-4, 1,-2), Vector(0, 0, 0)}, Vector(-4, 1,-2)}
					})
			);

			CAPTURE(std::get<0>(std::get<0>(p)));
			CAPTURE(std::get<1>(std::get<0>(p)));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(std::get<0>(p)) - std::get<1>(std::get<0>(p)) == std::get<1>(p));
		}
	}

	SECTION("Negate") {
		SECTION("negating a vector should produce another vector in the opposite direction") {
			auto p = GENERATE(
				table<Vector, Vector>({
					{Vector(0, 0, 0), Vector(0, 0, 0)},
					{Vector(1, 1, 1), Vector(-1, -1, -1)},
					{Vector(1, 2, 3), Vector(-1, -2, -3)},
					{Vector(-1,-2,-3), Vector(1, 2, 3)},
					{Vector(-3,-2,-1), Vector(3, 2, 1)},
					{Vector(-4, 1,-2), Vector(4, -1, 2)}
				})
			);

			CAPTURE(std::get<0>(p));
			CAPTURE(std::get<1>(p));

			REQUIRE(-std::get<0>(p) == std::get<1>(p));
		}
	}

	SECTION("Scalar-Multiplication") {
		SECTION("multiplying a vector with a scalar should produce another vector on the same direction") {
			auto p = GENERATE(
				table<std::tuple<Vector, float>, Vector>({
					{{Vector(0, 0, 0), 0}, Vector(0, 0, 0)},
					{{Vector(1, 1, 1), 0}, Vector(0, 0, 0)},
					{{Vector(1, 2, 3), 0}, Vector(0, 0, 0)},
					{{Vector(-1,-2,-3), 0}, Vector(0, 0, 0)},

					{{Vector(0, 0, 0), 1}, Vector(0, 0, 0)},
					{{Vector(1, 1, 1), 1}, Vector(1, 1, 1)},
					{{Vector(1, 2, 3), 1}, Vector(1, 2, 3)},
					{{Vector(-1,-2,-3), 1}, Vector(-1, -2, -3)},
					{{Vector(-3,-2,-1), 1}, Vector(-3, -2, -1)},
					{{Vector(-4, 1,-2), 1}, Vector(-4, 1, -2)},

					{{Vector(0, 0, 0), 2}, Vector(0, 0, 0)},
					{{Vector(1, 1, 1), 2}, Vector(2, 2, 2)},
					{{Vector(1, 2, 3), 2}, Vector(2, 4, 6)},
					{{Vector(-1,-2,-3), 2}, Vector(-2, -4, -6)},
					{{Vector(-3,-2,-1), 2}, Vector(-6, -4, -2)},
					{{Vector(-4, 1,-2), 2}, Vector(-8, 2, -4)},

					{{Vector(0, 0, 0), 2.5}, Vector(0, 0, 0)},
					{{Vector(1, 1, 1), 2.5}, Vector(2.5, 2.5, 2.5)},
					{{Vector(1, 2, 3), 2.5}, Vector(2.5, 5, 7.5)},
					{{Vector(-1,-2,-3), 2.5}, Vector(-2.5, -5, -7.5)},
					{{Vector(-3,-2,-1), 2.5}, Vector(-7.5, -5, -2.5)},
					{{Vector(-4, 1,-2), 2.5}, Vector(-10, 2.5, -5)}
				})
			);

			CAPTURE(std::get<0>(std::get<0>(p)));
			CAPTURE(std::get<1>(std::get<0>(p)));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(std::get<0>(p)) * std::get<1>(std::get<0>(p)) == std::get<1>(p));
		}

		SECTION("multiplying a vector with a negative scalar should produce another vector on the opposite direction") {
			auto p = GENERATE(
				table<std::tuple<Vector, float>, Vector>({
					{{Vector(0, 0, 0), -1}, Vector(0, 0, 0)},
					{{Vector(1, 1, 1), -1}, Vector(-1, -1, -1)},
					{{Vector(1, 2, 3), -1}, Vector(-1, -2, -3)},
					{{Vector(-1,-2,-3), -1}, Vector(1, 2, 3)},
					{{Vector(-3,-2,-1), -1}, Vector(3, 2, 1)},
					{{Vector(-4, 1,-2), -1}, Vector(4, -1, 2)},

					{{Vector(0, 0, 0), -2}, Vector(0, 0, 0)},
					{{Vector(1, 1, 1), -2}, Vector(-2, -2, -2)},
					{{Vector(1, 2, 3), -2}, Vector(-2, -4, -6)},
					{{Vector(-1,-2,-3), -2}, Vector(2, 4, 6)},
					{{Vector(-3,-2,-1), -2}, Vector(6, 4, 2)},
					{{Vector(-4, 1,-2), -2}, Vector(8, -2, 4)},

					{{Vector(0, 0, 0), -2.5}, Vector(0, 0, 0)},
					{{Vector(1, 1, 1), -2.5}, Vector(-2.5, -2.5, -2.5)},
					{{Vector(1, 2, 3), -2.5}, Vector(-2.5, -5, -7.5)},
					{{Vector(-1,-2,-3), -2.5}, Vector(2.5, 5, 7.5)},
					{{Vector(-3,-2,-1), -2.5}, Vector(7.5, 5, 2.5)},
					{{Vector(-4, 1,-2), -2.5}, Vector(10, -2.5, 5)}
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
				table<std::tuple<Vector, float>, Vector>({
					{{Vector(0, 0, 0), 1}, Vector(0, 0, 0)},
					{{Vector(1, 1, 1), 1}, Vector(1, 1, 1)},
					{{Vector(1, 2, 3), 1}, Vector(1, 2, 3)},
					{{Vector(-1,-2,-3), 1}, Vector(-1, -2, -3)},
					{{Vector(-3,-2,-1), 1}, Vector(-3, -2, -1)},
					{{Vector(-4, 1,-2), 1}, Vector(-4, 1, -2)},

					{{Vector(0, 0, 0), 2}, Vector(0, 0, 0)},
					{{Vector(1, 1, 1), 2}, Vector(0.5, 0.5, 0.5)},
					{{Vector(1, 2, 3), 2}, Vector(0.5, 1, 1.5)},
					{{Vector(-1,-2,-3), 2}, Vector(-0.5, -1, -1.5)},
					{{Vector(-3,-2,-1), 2}, Vector(-1.5, -1, -0.5)},
					{{Vector(-4, 1,-2), 2}, Vector(-2, 0.5, -1)},

					{{Vector(0, 0, 0), 2.5}, Vector(0, 0, 0)},
					{{Vector(1, 1, 1), 2.5}, Vector(0.4, 0.4, 0.4)},
					{{Vector(1, 2, 3), 2.5}, Vector(0.4, 0.8, 1.2)},
					{{Vector(-1,-2,-3), 2.5}, Vector(-0.4, -0.8, -1.2)},
					{{Vector(-3,-2,-1), 2.5}, Vector(-1.2, -0.8, -0.4)},
					{{Vector(-4, 1,-2), 2.5}, Vector(-1.6, 0.4, -0.8)}
					})
			);

			CAPTURE(std::get<0>(std::get<0>(p)));
			CAPTURE(std::get<1>(std::get<0>(p)));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(std::get<0>(p)) / std::get<1>(std::get<0>(p)) == std::get<1>(p));
		}

		SECTION("dividing a vector with a negativ scalar should produce another vector on the same direction") {
			auto p = GENERATE(
				table<std::tuple<Vector, float>, Vector>({
					{{Vector(0, 0, 0), -1}, Vector(0, 0, 0)},
					{{Vector(1, 1, 1), -1}, Vector(-1, -1, -1)},
					{{Vector(1, 2, 3), -1}, Vector(-1, -2, -3)},
					{{Vector(-1,-2,-3), -1}, Vector(1, 2, 3)},
					{{Vector(-3,-2,-1), -1}, Vector(3, 2, 1)},
					{{Vector(-4, 1,-2), -1}, Vector(4, -1, 2)},

					{{Vector(0, 0, 0), -2}, Vector(-0, -0, -0)},
					{{Vector(1, 1, 1), -2}, Vector(-0.5, -0.5, -0.5)},
					{{Vector(1, 2, 3), -2}, Vector(-0.5, -1, -1.5)},
					{{Vector(-1,-2,-3), -2}, Vector(0.5, 1, 1.5)},
					{{Vector(-3,-2,-1), -2}, Vector(1.5, 1, 0.5)},
					{{Vector(-4, 1,-2), -2}, Vector(2, -0.5, 1)},

					{{Vector(0, 0, 0), -2.5}, Vector(0, 0, 0)},
					{{Vector(1, 1, 1), -2.5}, Vector(-0.4, -0.4, -0.4)},
					{{Vector(1, 2, 3), -2.5}, Vector(-0.4, -0.8, -1.2)},
					{{Vector(-1,-2,-3), -2.5}, Vector(0.4, 0.8, 1.2)},
					{{Vector(-3,-2,-1), -2.5}, Vector(1.2, 0.8, 0.4)},
					{{Vector(-4, 1,-2), -2.5}, Vector(1.6, -0.4, 0.8)}
				})
			);

			CAPTURE(std::get<0>(std::get<0>(p)));
			CAPTURE(std::get<1>(std::get<0>(p)));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(std::get<0>(p)) / std::get<1>(std::get<0>(p)) == std::get<1>(p));
		}
	}

	SECTION("Magnitude") {
		SECTION("Unit-Vectors should have a magnitude of 1") {
			auto p = GENERATE(
				table<Vector, float>({
					{Vector(1, 0, 0), 1.},
					{Vector(0, 1, 0), 1.},
					{Vector(0, 0, 1), 1.},
					{Vector(12. / 13., 3. / 13., -4. / 13.), 1.},
					{Vector(1. / sqrt(2), 1. / sqrt(2), 0), 1.},
					{Vector(2. / sqrt(21), 4. / sqrt(21), 1. / sqrt(21)), 1.}
				})
			);

			CAPTURE(std::get<0>(p));
			CAPTURE(std::get<1>(p));

			REQUIRE(isClose(std::get<0>(p).length(), std::get<1>(p)));
		}

		SECTION("Vectors should have the right magnitude") {
			auto p = GENERATE(
				table<Vector, float>({
					{Vector(0, 0, 0), 0.},
					{Vector(1, 2, 3), sqrt(14)},
					{Vector(-1,-2,-3), sqrt(14)},
					{Vector(-3,-2,-1), sqrt(14)},
					{Vector(-4, 1,-2), sqrt(21)},
					{Vector(6, -1, 2), sqrt(41)},
					{Vector(6, 8, 10), sqrt(200)}
				})
			);

			CAPTURE(std::get<0>(p));
			CAPTURE(std::get<1>(p));

			REQUIRE(isClose(std::get<0>(p).length(), std::get<1>(p)));
		}
	}
	
	SECTION("Normalize") {
		SECTION("Unit-Vectors should stay the same") {
			auto p = GENERATE(
				table<Vector, Vector>({
					{
						Vector(1, 0, 0),
						Vector(1, 0, 0)
					},
					{
						Vector(0, 1, 0),
						Vector(0, 1, 0)
					},
					{
						Vector(0, 0, 1),
						Vector(0, 0, 1)
					},
					{
						Vector(12. / 13.,  3 / 13., -4 / 13.),
						Vector(12. / 13.,  3 / 13., -4 / 13.)
					},
					{
						Vector(1. / sqrt(2), 1. / sqrt(2), 0.),
						Vector(1. / sqrt(2), 1. / sqrt(2), 0.)
					},
					{
						Vector(2. / sqrt(21), 4. / sqrt(21), 1. / sqrt(21)),
						Vector(2. / sqrt(21), 4. / sqrt(21), 1. / sqrt(21))
					}
				})
			);

			CAPTURE(std::get<0>(p));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(p).normalize() == std::get<1>(p));
		}

		SECTION("Vectors should be normalized") {
			auto p = GENERATE(
				table<Vector, Vector>({
					{
						Vector(0, 0, 0),
						Vector(0, 0, 0)
					},
					{
						Vector(1, 2, 3),
						Vector(1. / sqrt(14), 2. / sqrt(14), 3. / sqrt(14))
					},
					{
						Vector(-1,-2,-3), 
						Vector(-1. / sqrt(14), -2. / sqrt(14), -3. / sqrt(14))
					},
					{
						Vector(-3,-2,-1),
						Vector(-3. / sqrt(14), -2. / sqrt(14), -1. / sqrt(14))
					},
					{
						Vector(-4, 1,-2),
						Vector(-4. / sqrt(21), 1. / sqrt(21), -2. / sqrt(21))
					},
					{
						Vector(6, -1, 2),
						Vector(6. / sqrt(41), -1. / sqrt(41), 2. / sqrt(41))
					},
					{
						Vector(6, 8, 10),
						Vector(6. / sqrt(200), 8. / sqrt(200), 10. / sqrt(200))
					}
				})
			);

			CAPTURE(std::get<0>(p));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(p).normalize() == std::get<1>(p));
		}
	}

	SECTION("Dot-Product") {
		SECTION("The Dot-Product of a Vector should be a scalar") {
			auto p = GENERATE(
				table<std::tuple<Vector, Vector>, float>({
					{{Vector(1, 2, 3), Vector(2, 3, 4)},	 20.},
					{{Vector(-2, 6, 8), Vector(1, -5, 7)},	 24.},
					{{Vector(1, 2, 3), Vector(-2, -3, -4)}, -20.},
					{{Vector(1, 2, 3), Vector(1, 2, 3)},	 14.},
					{{Vector(1, 2, 3), Vector(-1, -2, -3)}, -14.},
					{{Vector(1, 2, 3), Vector(0, 0, 0)},	 0.},
					{{Vector(0, 0, 0), Vector(0, 0, 0)},	 0.},
					{{Vector(1, 0, 0), Vector(-1, 0, 0)},	-1.},
					{{Vector(0, 1, 0), Vector(0, -1, 0)},	-1.},
					{{Vector(0, 0, 1), Vector(0, 0, -1)},	-1.},
					{{Vector(1, 0, 0), Vector(0, 1, 0)},	 0.},
					{{Vector(0, 1, 0), Vector(0, 0, 1)},	 0.},
					{{Vector(0, 0, 1), Vector(1, 0, 0)},	 0.},
					{{Vector(1, 0, 0), Vector(0, 0, 1)},	 0.},
					{{Vector(0, 1, 0), Vector(1, 0, 0)},	 0.},
					{{Vector(0, 0, 1), Vector(0, 1, 0)},	 0.},
					{{Vector(0, 1, 1), Vector(0, 1, 0)},	 1.}
				})
			);

			CAPTURE(std::get<0>(std::get<0>(p)));
			CAPTURE(std::get<1>(std::get<0>(p)));
			CAPTURE(std::get<1>(p));

			REQUIRE(isClose(std::get<0>(std::get<0>(p)).dot(std::get<1>(std::get<0>(p))), std::get<1>(p)));
		}
	}

	SECTION("Cross-Product") {
		SECTION("The Cross-Product of a Vector should be a Vector") {
			auto p = GENERATE(
				table<std::tuple<Vector, Vector>, Vector>({
					{
						{Vector(1, 2, 3), Vector(2, 3, 4)},
						Vector(-1, 2, -1)
					},
					{
						{Vector(-2, 6, 8), Vector(1, -5, 7)},
						Vector(82, 22, 4)
					},
					{
						{Vector(1, 2, 3), Vector(-2, -3, -4)},
						Vector(1, -2, 1)
					},
					{
						{Vector(1, 2, 3), Vector(1, 2, 3)},
						Vector(0, 0, 0)
					},
					{
						{Vector(1, 2, 3), Vector(-1, -2, -3)},
						Vector(0, 0, 0)
					},
					{
						{Vector(1, 2, 3), Vector(0, 0, 0)},
						Vector(0, 0, 0)
					},
					{
						{Vector(0, 0, 0), Vector(0, 0, 0)},
						Vector(0, 0, 0)
					},
					{
						{Vector(1, 0, 0), Vector(-1, 0, 0)},
						Vector(0, 0, 0)
					},
					{
						{Vector(0, 1, 0), Vector(0, -1, 0)},
						Vector(0, 0, 0)
					},
					{
						{Vector(0, 0, 1), Vector(0, 0, -1)},
						Vector(0, 0, 0)
					},
					{
						{Vector(1, 0, 0), Vector(0, 1, 0)},
						Vector(0, 0, 1)
					},
					{
						{Vector(0, 1, 0), Vector(0, 0, 1)},
						Vector(1, 0, 0)
					},
					{
						{Vector(0, 0, 1), Vector(1, 0, 0)},
						Vector(0, 1, 0)
					},
					{
						{Vector(1, 0, 0), Vector(0, 0, 1)},
						Vector(0, -1, 0)
					}
				})
			);

			CAPTURE(std::get<0>(std::get<0>(p)));
			CAPTURE(std::get<1>(std::get<0>(p)));
			CAPTURE(std::get<1>(p));

			REQUIRE(std::get<0>(std::get<0>(p)).cross(std::get<1>(std::get<0>(p))) == std::get<1>(p));
		}
	}
}