#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <ctime>
#include <limits>
#include <tuple>
#include <cmath>

#include "utils/Util.hpp"
#include "graphics/Transformation.hpp"
#include "graphics/Material.hpp"
#include "graphics/Sphere.hpp"
#include "graphics/Point.hpp"


TEST_CASE("Sphere") {
	srand((unsigned)time(0));

	SECTION("Initialize") {
		Sphere sp;


		REQUIRE(sp.material == BasicMaterial(Color(1, 1, 1), 0.1, 0.9, 0.9, 200));
		REQUIRE(sp.transform == Matrix::Identity());
	}

	SECTION("Transformation") {
		Sphere sp;

		sp.transform = sp.transform * Transformation::Scaling(2, 2, 2) * Transformation::Translation(1, 0, -1);
		REQUIRE(sp.transform == Transformation::Scaling(2, 2, 2) * Transformation::Translation(1, 0, -1));
	}

	SECTION("Normal") {
		SECTION("Unit") {
			Sphere sp;

			auto p = GENERATE(
				table<Point, Vector>({
					{Point(1, 0, 0), Vector(1, 0, 0)},
					{Point(0, 1, 0), Vector(0, 1, 0)},
					{Point(0, 0, 1), Vector(0, 0, 1)},
					{Point(sqrt(3)/3, sqrt(3) / 3, sqrt(3) / 3), Vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3) },
				})
			);

			CAPTURE(std::get<0>(p));
			CAPTURE(std::get<1>(p));

			REQUIRE(sp.normalAt(std::get<0>(p)) == std::get<1>(p));
			REQUIRE(std::get<1>(p).normalize() == std::get<1>(p));
		}

		SECTION("Translated") {
			Sphere sp;
			sp.transform = Transformation::Translation(0, 1, 0);
			Vector normal = sp.normalAt(Point(0, 1.70711, -0.70711));

			REQUIRE(isClose(normal, Vector(0, 0.70711, -0.70711)));
			REQUIRE(isClose(normal.normalize(), Vector(0, 0.70711, -0.70711)));
		}

		SECTION("Transformed") {
			Sphere sp;
			sp.transform = Transformation::Scaling(1, 0.5, 1) * Transformation::RotationZ(M_PI/5);
			Vector normal = sp.normalAt(Point(0, sqrt(2)/2, -sqrt(2) / 2));

			REQUIRE(isClose(normal, Vector(0, 0.97014, -0.24254)));
			REQUIRE(isClose(normal.normalize(), Vector(0, 0.97014, -0.24254)));
		}
	}
}