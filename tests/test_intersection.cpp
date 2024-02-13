#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include "../src/intersection.hpp"
#include "../src/sphere.hpp"

TEST(Intersection, Init) {
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1.f);
    Nyx::Intersection i = Nyx::Intersection(3.5f, &s);
    EXPECT_EQ(i.t, 3.5);
    EXPECT_EQ(*i.object, s);
}

TEST(Intersection, Hit) {
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1.f);
    Nyx::Intersection i1 = Nyx::Intersection(3.5f, &s);
    Nyx::Intersection i2 = Nyx::Intersection(2.5f, &s);
    Nyx::Intersection i3 = Nyx::Intersection(1.5f, &s);
    Nyx::Intersection i4 = Nyx::Intersection(0.5f, &s);
    Nyx::Intersection i5 = Nyx::Intersection(-1.5f, &s);
    Nyx::Intersection i6 = Nyx::Intersection(-2.5f, &s);
    Nyx::Intersection i7 = Nyx::Intersection(-3.5f, &s);
    Nyx::Intersection i8 = Nyx::Intersection(-4.5f, &s);

    std::vector<Nyx::Intersection> xs = {i1, i2, i3, i4, i5, i6, i7, i8};

    Nyx::Intersection i = Nyx::Intersection::hit(xs);
    EXPECT_EQ(i.t, 0.5);
    EXPECT_EQ(*i.object, s);
}

TEST(Intersection, HitNegative) {
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1.f);
    Nyx::Intersection i5 = Nyx::Intersection(-1.5f, &s);
    Nyx::Intersection i6 = Nyx::Intersection(-2.5f, &s);
    Nyx::Intersection i7 = Nyx::Intersection(-3.5f, &s);
    Nyx::Intersection i8 = Nyx::Intersection(-4.5f, &s);

    std::vector<Nyx::Intersection> xs = {i5, i6, i7, i8};

    Nyx::Intersection i = Nyx::Intersection::hit(xs);
    EXPECT_EQ(i.t, 0);
    EXPECT_EQ(i.object, nullptr);
}

TEST(Intersection, HitRandomOrder) {
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1.f);
    Nyx::Intersection i1 = Nyx::Intersection(3.5f, &s);
    Nyx::Intersection i2 = Nyx::Intersection(2.5f, &s);
    Nyx::Intersection i3 = Nyx::Intersection(1.5f, &s);
    Nyx::Intersection i4 = Nyx::Intersection(0.5f, &s);
    Nyx::Intersection i5 = Nyx::Intersection(-1.5f, &s);
    Nyx::Intersection i6 = Nyx::Intersection(-2.5f, &s);
    Nyx::Intersection i7 = Nyx::Intersection(-3.5f, &s);
    Nyx::Intersection i8 = Nyx::Intersection(-4.5f, &s);

    std::vector<Nyx::Intersection> xs = {i1, i2, i3, i4, i5, i6, i7, i8};
    Nyx::Intersection hit = Nyx::Intersection::hit(xs);

    for (int i = 0; i < 100; i++) {
        std::random_shuffle(xs.begin(), xs.end());
        hit = Nyx::Intersection::hit(xs);
        ASSERT_EQ(hit.t, 0.5);
        ASSERT_EQ(*hit.object, s);
    }
}