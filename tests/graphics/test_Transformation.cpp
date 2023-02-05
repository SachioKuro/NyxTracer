#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <ctime>
#include <limits>
#include <tuple>

#include "utils/Util.hpp"
#include "graphics/Transformation.hpp"
#include "graphics/Matrix.hpp"
#include "graphics/Vector.hpp"
#include "graphics/Point.hpp"

TEST_CASE("Transformation") {
	srand((unsigned)time(0));

	SECTION("Translation") {
		Matrix translation = Transformation::Translation(5, -3, 2);
		Point src(-3, 4, 5);
		Point dst(2, 1, 7);

		REQUIRE(translation * src == dst);
	}

	SECTION("Reverse Translation") {
		Matrix translation = Transformation::Translation(5, -3, 2);
		Matrix invTranslation = translation.inverse();
		Point src(-3, 4, 5);
		Point dst(-8, 7, 3);

		REQUIRE(invTranslation * src == dst);
	}

	SECTION("Translation does not effect Vector") {
		Matrix translation = Transformation::Translation(5, -3, 2);
		Vector v(-3, 4, 5);

		REQUIRE(translation * v == v);
	}

	SECTION("Scaling Point") {
		Matrix scaling = Transformation::Scaling(2, 3, 4);
		Point orig(-4, 6, 8);
		Point scaled(-8, 18, 32);

		REQUIRE(scaling * orig == scaled);
	}

	SECTION("Scaling Vector") {
		Matrix scaling = Transformation::Scaling(2, 3, 4);
		Vector orig(-4, 6, 8);
		Vector scaled(-8, 18, 32);

		REQUIRE(scaling * orig == scaled);
	}

	SECTION("Inverse Scaling Vector") {
		Matrix scaling = Transformation::Scaling(2, 3, 4);
		Matrix invScaling = scaling.inverse();
		Vector orig(-4, 6, 8);
		Vector scaled(-2, 2, 2);

		REQUIRE(invScaling * orig == scaled);
	}

	SECTION("Reflection") {
		Matrix scaling = Transformation::Scaling(-1, 1, 1);
		Point orig(-4, 6, 8);
		Point reflected(4, 6, 8);

		REQUIRE(scaling * orig == reflected);
	}

	SECTION("Rotation X") {
		Matrix rotationHalfQuarter = Transformation::RotationX(M_PI / 4);
		Matrix rotationFullQuarter = Transformation::RotationX(M_PI / 2);
		Matrix rotationFull = Transformation::RotationX(2 * M_PI);
		Point p(0, 1, 0);

		REQUIRE(isClose(rotationHalfQuarter * p, Point(0, sqrt(2) / 2, sqrt(2) / 2)));
		REQUIRE(isClose(rotationFullQuarter * p, Point(0, 0, 1)));
		REQUIRE(isClose(rotationFull * p, p));
	}

	SECTION("Inverse Rotation X") {
		Matrix rotationHalfQuarter = Transformation::RotationX(M_PI / 4);
		Matrix inverseRotationHalfQuarter = rotationHalfQuarter.inverse();
		Point p(0, 1, 0);

		REQUIRE(isClose(inverseRotationHalfQuarter * p, Point(0, sqrt(2) / 2, -sqrt(2) / 2)));
	}

	SECTION("Rotation Y") {
		Matrix rotationHalfQuarter = Transformation::RotationY(M_PI / 4);
		Matrix rotationFullQuarter = Transformation::RotationY(M_PI / 2);
		Matrix rotationFull = Transformation::RotationY(2 * M_PI);
		Point p(0, 0, 1);

		REQUIRE(isClose(rotationHalfQuarter * p, Point(sqrt(2) / 2, 0, sqrt(2) / 2)));
		REQUIRE(isClose(rotationFullQuarter * p, Point(1, 0, 0)));
		REQUIRE(isClose(rotationFull * p, p));
	}

	SECTION("Inverse Rotation Y") {
		Matrix rotationHalfQuarter = Transformation::RotationY(M_PI / 4);
		Matrix inverseRotationHalfQuarter = rotationHalfQuarter.inverse();
		Point p(0, 0, 1);

		REQUIRE(isClose(inverseRotationHalfQuarter * p, Point(-sqrt(2) / 2, 0, sqrt(2) / 2)));
	}

	SECTION("Rotation Z") {
		Matrix rotationHalfQuarter = Transformation::RotationZ(M_PI / 4);
		Matrix rotationFullQuarter = Transformation::RotationZ(M_PI / 2);
		Matrix rotationFull = Transformation::RotationZ(2 * M_PI);
		Point p(0, 1, 0);

		REQUIRE(isClose(rotationHalfQuarter * p, Point(-sqrt(2) / 2, sqrt(2) / 2, 0)));
		REQUIRE(isClose(rotationFullQuarter * p, Point(-1, 0, 0)));
		REQUIRE(isClose(rotationFull * p, p));
	}

	SECTION("Inverse Rotation Z") {
		Matrix rotationHalfQuarter = Transformation::RotationZ(M_PI / 4);
		Matrix inverseRotationHalfQuarter = rotationHalfQuarter.inverse();
		Point p(0, 1, 0);

		REQUIRE(isClose(inverseRotationHalfQuarter * p, Point(sqrt(2) / 2, sqrt(2) / 2, 0)));
	}
}