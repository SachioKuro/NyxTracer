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
    Nyx::Point original_light_position = w.lights[0].position;
    w.lights[0].position = Nyx::Point(-11, 11, -10);
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 0, -5), Nyx::Vector(0, 0, 1));
    auto s = w.objects[0];
    auto i = Nyx::Intersection(4, s);
    auto hit = Nyx::Hit(i, r);
    auto c = w.shade_hit(hit);
    EXPECT_EQ(c, Nyx::Color(0.36043, 0.45054, 0.27032));
    w.lights[0].position = original_light_position;
}

TEST(World, ShadeHitInside) {
    Nyx::World w = Nyx::World::default_world();
    w.lights[0] = Nyx::PointLight(Nyx::Point(0, 0.25, 0), Nyx::Color(1, 1, 1));
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 0, 0), Nyx::Vector(0, 0, 1));
    auto s = w.objects[1];
    auto i = Nyx::Intersection(0.5, s);
    auto hit = Nyx::Hit(i, r);
    auto c = w.shade_hit(hit);
    EXPECT_EQ(c, Nyx::Color(0.90482, 0.90482, 0.90482));
}

TEST(World, ShadeHitShadow) {
    Nyx::World w;
    w.lights.push_back(Nyx::PointLight(Nyx::Point(0, 0, -10), Nyx::Color(1, 1, 1)));
    Nyx::Sphere s1 = Nyx::Sphere();
    w.objects.push_back(&s1);
    Nyx::Sphere s2 = Nyx::Sphere();
    s2.set_transform(Nyx::Transformation::translation(0, 0, 10));
    w.objects.push_back(&s2);
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 0, 5), Nyx::Vector(0, 0, 1));
    auto i = Nyx::Intersection(4, &s2);
    auto hit = Nyx::Hit(i, r);
    auto c = w.shade_hit(hit);
    EXPECT_EQ(c, Nyx::Color(0.1, 0.1, 0.1));
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
    EXPECT_EQ(c, w.objects[1]->material.pattern->at(Nyx::Point(0, 0, 0)));
}

TEST(World, IsShadowedNoShadow) {
    Nyx::World w = Nyx::World::default_world();
    Nyx::Point p = Nyx::Point(0, 10, 0);
    EXPECT_FALSE(w.is_shadowed(p, w.lights[0]));
}

TEST(World, IsShadowedShadow) {
    Nyx::World w = Nyx::World::default_world();
    Nyx::Point p = Nyx::Point(10, -10, 10);
    EXPECT_TRUE(w.is_shadowed(p, w.lights[0]));
}

TEST(World, IsShadowedNoShadowOtherSide) {
    Nyx::World w = Nyx::World::default_world();
    Nyx::Point p = Nyx::Point(-20, 20, -20);
    EXPECT_FALSE(w.is_shadowed(p, w.lights[0]));
}

TEST(World, IsShadowedNoShadowBetween) {
    Nyx::World w = Nyx::World::default_world();
    Nyx::Point p = Nyx::Point(-2, 2, -2);
    EXPECT_FALSE(w.is_shadowed(p, w.lights[0]));
}