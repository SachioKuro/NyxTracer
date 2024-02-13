#include <gtest/gtest.h>
#include "../src/ray.hpp"
#include "../src/transformation.hpp"

TEST(Ray, Init) {
    Nyx::Point origin = Nyx::Point(1, 2, 3);
    Nyx::Vector direction = Nyx::Vector(4, 5, 6);
    Nyx::Ray r = Nyx::Ray(origin, direction);
    EXPECT_EQ(r.origin, origin);
    EXPECT_EQ(r.direction, direction);
}

TEST(Ray, Position) {
    Nyx::Ray r = Nyx::Ray(Nyx::Point(2, 3, 4), Nyx::Vector(1, 0, 0));
    EXPECT_EQ(r.position(0), Nyx::Point(2, 3, 4));
    EXPECT_EQ(r.position(1), Nyx::Point(3, 3, 4));
    EXPECT_EQ(r.position(-1), Nyx::Point(1, 3, 4));
    EXPECT_EQ(r.position(2.5), Nyx::Point(4.5, 3, 4));
}

TEST(Ray, Position2) {
    Nyx::Ray r = Nyx::Ray(Nyx::Point(2, 3, 4), Nyx::Vector(0, 1, 0));
    EXPECT_EQ(r.position(0), Nyx::Point(2, 3, 4));
    EXPECT_EQ(r.position(1), Nyx::Point(2, 4, 4));
    EXPECT_EQ(r.position(-1), Nyx::Point(2, 2, 4));
    EXPECT_EQ(r.position(2.5), Nyx::Point(2, 5.5, 4));
}

TEST(Ray, Position3) {
    Nyx::Ray r = Nyx::Ray(Nyx::Point(2, 3, 4), Nyx::Vector(0, 0, 1));
    EXPECT_EQ(r.position(0), Nyx::Point(2, 3, 4));
    EXPECT_EQ(r.position(1), Nyx::Point(2, 3, 5));
    EXPECT_EQ(r.position(-1), Nyx::Point(2, 3, 3));
    EXPECT_EQ(r.position(2.5), Nyx::Point(2, 3, 6.5));
}

TEST(Ray, Position4) {
    Nyx::Ray r = Nyx::Ray(Nyx::Point(2, 3, 4), Nyx::Vector(1, 2, 3));
    EXPECT_EQ(r.position(0), Nyx::Point(2, 3, 4));
    EXPECT_EQ(r.position(1), Nyx::Point(3, 5, 7));
    EXPECT_EQ(r.position(-1), Nyx::Point(1, 1, 1));
    EXPECT_EQ(r.position(2.5), Nyx::Point(4.5, 8, 11.5));
}

TEST(Ray, Translate) {
    Nyx::Ray r = Nyx::Ray(Nyx::Point(1, 2, 3), Nyx::Vector(0, 1, 0));
    Nyx::Matrix<4> m = Nyx::Transformation::translation(3, 4, 5);
    Nyx::Ray r2 = r.transform(m);
    EXPECT_EQ(r2.origin, Nyx::Point(4, 6, 8));
    EXPECT_EQ(r2.direction, Nyx::Vector(0, 1, 0));
}

TEST(Ray, Scale) {
    Nyx::Ray r = Nyx::Ray(Nyx::Point(1, 2, 3), Nyx::Vector(0, 1, 0));
    Nyx::Matrix<4> m = Nyx::Transformation::scaling(2, 3, 4);
    Nyx::Ray r2 = r.transform(m);
    EXPECT_EQ(r2.origin, Nyx::Point(2, 6, 12));
    EXPECT_EQ(r2.direction, Nyx::Vector(0, 3, 0));
}