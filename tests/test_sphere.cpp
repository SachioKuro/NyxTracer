#include <gtest/gtest.h>
#include "../src/sphere.hpp"

#include "../src/ray.hpp"

TEST(Sphere, Init) {
    Nyx::Point center = Nyx::Point(1, 2, 3);
    float radius = 4;
    Nyx::Sphere s = Nyx::Sphere(center, radius);
    EXPECT_EQ(s.center, center);
    EXPECT_EQ(s.radius, radius);
}

TEST(Sphere, RayIntersectCenter) {
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1);
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 0, -5), Nyx::Vector(0, 0, 1));
    auto xs = s.intersect(r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 6);
}

TEST(Sphere, RayIntersectTangent) {
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1);
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 1, -5), Nyx::Vector(0, 0, 1));
    auto xs = s.intersect(r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 5);
    EXPECT_EQ(xs[1].t, 5);
}

TEST(Sphere, RayIntersectMiss) {
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1);
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 2, -5), Nyx::Vector(0, 0, 1));
    auto xs = s.intersect(r);
    EXPECT_EQ(xs.size(), 0);
}

TEST(Sphere, RayIntersectInside) {
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1);
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 0, 0), Nyx::Vector(0, 0, 1));
    auto xs = s.intersect(r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, -1);
    EXPECT_EQ(xs[1].t, 1);
}

TEST(Sphere, RayIntersectBehind) {
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1);
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 0, 5), Nyx::Vector(0, 0, 1));
    auto xs = s.intersect(r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, -6);
    EXPECT_EQ(xs[1].t, -4);
}

TEST(Sphere, RayIntersectScaled) {
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1);
    s.set_transform(Nyx::Transformation::identity().scale(2, 2, 2));
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 0, -5), Nyx::Vector(0, 0, 1));
    auto xs = s.intersect(r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 3);
    EXPECT_EQ(xs[1].t, 7);
}

TEST(Sphere, RayIntersectTranslated) {
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1);
    s.set_transform(Nyx::Transformation::identity().translate(5, 0, 0));
    Nyx::Ray r = Nyx::Ray(Nyx::Point(0, 0, -5), Nyx::Vector(0, 0, 1));
    auto xs = s.intersect(r);
    EXPECT_EQ(xs.size(), 0);
}

TEST(Sphere, NormalAtX) {
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1);
    Nyx::Vector n = s.normal_at(Nyx::Point(1, 0, 0));
    EXPECT_EQ(n, Nyx::Vector(1, 0, 0));
}

TEST(Sphere, NormalAtY) {
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1);
    Nyx::Vector n = s.normal_at(Nyx::Point(0, 1, 0));
    EXPECT_EQ(n, Nyx::Vector(0, 1, 0));
    EXPECT_EQ(n, n.normalize());
}

TEST(Sphere, NormalAtZ) {
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1);
    Nyx::Vector n = s.normal_at(Nyx::Point(0, 0, 1));
    EXPECT_EQ(n, Nyx::Vector(0, 0, 1));
    EXPECT_EQ(n, n.normalize());
}

TEST(Sphere, NormalAtNonAxial) {
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1);
    Nyx::Vector n = s.normal_at(Nyx::Point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
    EXPECT_EQ(n, Nyx::Vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
    EXPECT_EQ(n, n.normalize());
}

TEST(Sphere, NormalAtTranslated) {
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1);
    s.set_transform(Nyx::Transformation::identity().translate(0, 1, 0));
    Nyx::Vector n = s.normal_at(Nyx::Point(0, 1.70711, -0.70711));
    EXPECT_EQ(n, Nyx::Vector(0, 0.70711, -0.70711));
    EXPECT_EQ(n, n.normalize());
}

TEST(Sphere, NormalAtTransformed) {
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1);
    Nyx::Matrix<4> m = Nyx::Transformation::identity().rotateZ(M_PI/5).scale(1, 0.5, 1).matrix();
    s.set_transform(m);
    Nyx::Vector n = s.normal_at(Nyx::Point(0, sqrt(2)/2, -sqrt(2)/2));
    EXPECT_EQ(n, Nyx::Vector(0, 0.97014, -0.24254));
    EXPECT_EQ(n, n.normalize());
}