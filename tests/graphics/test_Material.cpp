#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <ctime>
#include <limits>
#include <tuple>
#include <cmath>

#include "utils/Util.hpp"
#include "graphics/Light.hpp"
#include "graphics/Material.hpp"
#include "graphics/Color.hpp"


TEST_CASE("Material") {
	srand((unsigned)time(0));

	SECTION("Initialize") {
		Color color(1, 1, 1);
		float ambient = 0.1;
		float diffuse = 0.9;
		float specular = 0.9;
		float shininess = 0.1;
		BasicMaterial mat(color, ambient, diffuse, specular, shininess);

		REQUIRE(mat.color == color);
		REQUIRE(mat.ambient == ambient);
		REQUIRE(mat.diffuse == diffuse);
		REQUIRE(mat.specular == specular);
		REQUIRE(mat.shininess == shininess);
	}

	SECTION("Lighting") {
		BasicMaterial mat(Color(1, 1, 1), .1, .9, .9, 200);
		Point pos(0, 0, 0);

		SECTION("Eye between light and surface") {
			Vector eye(0, 0, -1);
			Vector normal(0, 0, -1);
			PointLight pointLight(Point(0, 0, -10), Color(1, 1, 1));

			REQUIRE(mat.lighting(pointLight, pos, eye, normal) == Color(1.9, 1.9, 1.9));
		}

		SECTION("Eye 45° offset") {
			Vector eye(0, sqrt(2) / 2, sqrt(2) / 2);
			Vector normal(0, 0, -1);
			PointLight pointLight(Point(0, 0, -10), Color(1, 1, 1));

			REQUIRE(mat.lighting(pointLight, pos, eye, normal) == Color(1, 1, 1));
		}

		SECTION("Point-Light 45° offset") {
			Vector eye(0, 0, -1);
			Vector normal(0, 0, -1);
			PointLight pointLight(Point(0, 10, -10), Color(1, 1, 1));

			REQUIRE(mat.lighting(pointLight, pos, eye, normal) == Color(0.7364, 0.7364, 0.7364));
		}

		SECTION("Point-Light and Eye 45° offset, but appart from another") {
			Vector eye(0, -sqrt(2) / 2, -sqrt(2) / 2);
			Vector normal(0, 0, -1);
			PointLight pointLight(Point(0, 10, -10), Color(1, 1, 1));

			REQUIRE(mat.lighting(pointLight, pos, eye, normal) == Color(1.6364, 1.6364, 1.6364));
		}

		SECTION("Eye between light and surface") {
			Vector eye(0, 0, -1);
			Vector normal(0, 0, -1);
			PointLight pointLight(Point(0, 0, 10), Color(1, 1, 1));

			REQUIRE(mat.lighting(pointLight, pos, eye, normal) == Color(.1, .1, .1));
		}
	}
}