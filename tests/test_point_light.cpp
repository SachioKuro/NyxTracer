#include <gtest/gtest.h>
#include "../src/point_light.hpp"

TEST(PointLight, Init) {
    Nyx::Point position = Nyx::Point(0, -1, 0);
    Nyx::Color intensity = Nyx::Color(1, 1, 1);
    Nyx::PointLight light = Nyx::PointLight(position, intensity);
    EXPECT_EQ(light.position, position);
    EXPECT_EQ(light.intensity, intensity);
}