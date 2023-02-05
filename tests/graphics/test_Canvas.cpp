#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <algorithm>
#include <tuple>
#include <string>
#include <vector>
#include <ranges>

#include "utils/Util.hpp"
#include "graphics/Canvas.hpp"
#include "graphics/Color.hpp"

TEST_CASE("Canvas") {
	srand((unsigned)time(0));
	
	SECTION("Initialize") {
		SECTION("create a canvas with all black pixels") {
			int width = randomInt(100, 2000);
			int height = randomInt(100, 2000);
			Canvas c(width, height);
			REQUIRE(c.width() == width);
			REQUIRE(c.height() == height);
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < height; j++) {
					REQUIRE(c(i, j) == Color(0, 0, 0));
				}
			}
		}
	}

	SECTION("Mutating Canvas") {
		SECTION("Setting and getting pixels") {
			Canvas c(10, 20);
			Color red(1, 0, 0);
			Color black(0, 0, 0);
			Color blue(0, 0, 1, .5);
			c(2, 3) = red;
			c(3, 2) = blue;
			REQUIRE(c(2, 3) == red);
			REQUIRE(c(3, 2) == blue);
			REQUIRE(c(3, 3) == black);
		}
	}
	
	SECTION("Exporting Canvas") {
		using std::ranges::to;
		using std::ranges::views::split;
		using std::ranges::views::take;
		using std::ranges::views::drop;
		using std::ranges::views::transform;
		
		SECTION("PPM header") {
			Canvas c(5, 3);
			std::string ppm = c.toPPM();
			auto r = ppm | split('\n') | take(3);
			auto v = to<std::vector<std::string>>(r);
			REQUIRE(v.at(0) == "P3");
			REQUIRE(v.at(1) == "5 3");
			REQUIRE(v.at(2) == "255");
		}

		SECTION("Valid pixel section") {
			Canvas c(10, 3);
			Color red(1, 0, 0);
			Color green(0, 1, 0);
			Color blue(0, 0, 1);
			for (int i = 0; i < 10; i++) {
				c(i, 0) = red;
				c(i, 1) = green;
				c(i, 2) = blue;
			}
			std::string ppm = c.toPPM();
			auto r = ppm | split('\n') | drop(3);
			auto lineSizes = r | transform([](auto s) { return s.size(); });
			auto v = to<std::vector<std::string>>(r);
			
			REQUIRE(std::all_of(lineSizes.begin(), lineSizes.end(), [](auto s) { return s <= 70; }));
			REQUIRE(v.size() == 7);
			REQUIRE(v.at(0) == "255 0 0 255 0 0 255 0 0 255 0 0 255 0 0");
			REQUIRE(v.at(1) == "255 0 0 255 0 0 255 0 0 255 0 0 255 0 0");
			REQUIRE(v.at(2) == "0 255 0 0 255 0 0 255 0 0 255 0 0 255 0");
			REQUIRE(v.at(3) == "0 255 0 0 255 0 0 255 0 0 255 0 0 255 0");
			REQUIRE(v.at(4) == "0 0 255 0 0 255 0 0 255 0 0 255 0 0 255");
			REQUIRE(v.at(5) == "0 0 255 0 0 255 0 0 255 0 0 255 0 0 255");
			REQUIRE(v.at(6) == "");
		}
	}
}