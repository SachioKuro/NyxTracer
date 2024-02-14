#include <gtest/gtest.h>
#include "../src/world.hpp"
#include "../src/ray.hpp"
#include "../src/intersection.hpp"
#include "../src/hit.hpp"
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

TEST(World, ShadeHit) {
    Nyx::World w = Nyx::World::default_world();
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 0, -5), Nyx::Vector(0, 0, 1));
    auto s = w.objects[0];
    auto i = Nyx::Intersection(4, s);
    auto hit = Nyx::Hit(i, r);
    auto c = w.shade_hit(hit);
    EXPECT_EQ(c, Nyx::Color(0.38066, 0.47583, 0.2855));
}

TEST(World, ShadeHitInside) {
    Nyx::World w = Nyx::World::default_world();
    w.lights[0] = Nyx::PointLight(Nyx::Point(0, 0.25, 0), Nyx::Color(1, 1, 1));
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 0, 0), Nyx::Vector(0, 0, 1));
    auto s = w.objects[1];
    auto i = Nyx::Intersection(0.5, s);
    auto hit = Nyx::Hit(i, r);
    auto c = w.shade_hit(hit);
    EXPECT_EQ(c, Nyx::Color(0.90498, 0.90498, 0.90498));
}

TEST(World, ColorAtNoHit) {
    Nyx::World w = Nyx::World::default_world();
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 0, -5), Nyx::Vector(0, 1, 0));
    auto c = w.color_at(r);
    EXPECT_EQ(c, Nyx::Color(0, 0, 0));
}

TEST(World, ColorAt) {
    Nyx::World w = Nyx::World::default_world();
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 0, -5), Nyx::Vector(0, 0, 1));
    auto c = w.color_at(r);
    EXPECT_EQ(c, Nyx::Color(0.38066, 0.47583, 0.2855));
}

TEST(World, ColorAtInside) {
    Nyx::World w = Nyx::World::default_world();
    w.objects[0]->material.ambient = 1;
    w.objects[1]->material.ambient = 1;
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 0, 0.75), Nyx::Vector(0, 0, -1));
    auto c = w.color_at(r);
    EXPECT_EQ(c, w.objects[1]->material.color);
}