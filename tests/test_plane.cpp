#include <gtest/gtest.h>
#include "../src/plane.hpp"
#include "../src/tuple.hpp"

TEST(Plane, Normal) {
    Nyx::Plane p = Nyx::Plane();
    Nyx::Vector n1 = p.normal_at(Nyx::Point(0, 0, 0));
    Nyx::Vector n2 = p.normal_at(Nyx::Point(10, 0, -10));
    Nyx::Vector n3 = p.normal_at(Nyx::Point(-5, 0, 150));
    EXPECT_EQ(n1, Nyx::Vector(0, 1, 0));
    EXPECT_EQ(n2, Nyx::Vector(0, 1, 0));
    EXPECT_EQ(n3, Nyx::Vector(0, 1, 0));
}

TEST(Plane, IntersectParallel) {
    Nyx::Plane p = Nyx::Plane();
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 10, 0), Nyx::Vector(0, 0, 1));
    auto xs = p.intersect(r);
    ASSERT_EQ(xs.size(), 0);
}

TEST(Plane, IntersectCoplanar) {
    Nyx::Plane p = Nyx::Plane();
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 0, 0), Nyx::Vector(0, 0, 1));
    auto xs = p.intersect(r);
    ASSERT_EQ(xs.size(), 0);
}

TEST(Plane, IntersectFromAbove) {
    Nyx::Plane p = Nyx::Plane();
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 1, 0), Nyx::Vector(0, -1, 0));
    auto xs = p.intersect(r);
    ASSERT_EQ(xs.size(), 1);
    EXPECT_EQ(xs[0].t, 1);
    EXPECT_EQ(xs[0].object, &p);
}

TEST(Plane, IntersectFromBelow) {
    Nyx::Plane p = Nyx::Plane();
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, -1, 0), Nyx::Vector(0, 1, 0));
    auto xs = p.intersect(r);
    ASSERT_EQ(xs.size(), 1);
    EXPECT_EQ(xs[0].t, 1);
    EXPECT_EQ(xs[0].object, &p);
}
