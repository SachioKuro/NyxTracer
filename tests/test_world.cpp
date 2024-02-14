#include <gtest/gtest.h>
#include "../src/world.hpp"
#include "../src/uid.hpp"
#include "../src/sphere.hpp"
#include "../src/point_light.hpp"

TEST(World, Init) {
    Nyx::World w = Nyx::World();
    EXPECT_EQ(w.objects.size(), 0);
    EXPECT_EQ(w.lights.size(), 0);
}

TEST(World, Intersect) {
    Nyx::World w = Nyx::World::default_world();
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 0, -5), Nyx::Vector(0, 0, 1));
    auto xs = w.intersect(r);
    ASSERT_EQ(xs.size(), 4);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 4.5);
    EXPECT_EQ(xs[2].t, 5.5);
    EXPECT_EQ(xs[3].t, 6);
}