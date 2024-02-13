#include <gtest/gtest.h>
#include "../src/tuple.hpp"

TEST(Point, Init) {
    Nyx::Point p = Nyx::Point{4.3f, -4.2f, 3.1f};
    EXPECT_FLOAT_EQ(p.x, 4.3f);
    EXPECT_FLOAT_EQ(p.y, -4.2f);
    EXPECT_FLOAT_EQ(p.z, 3.1f);
    EXPECT_FLOAT_EQ(p.w, 1.f);
}

TEST(Point, Equal) {
    Nyx::Point p1 = Nyx::Point{4.3f, -4.2f, 3.1f};
    Nyx::Point p2 = Nyx::Point{4.3f, -4.2f, 3.1f};
    EXPECT_EQ(p1, p2);
}

TEST(Point, Add) {
    Nyx::Point p1 = Nyx::Point{3.1f, -2.3f, 5.4f};
    Nyx::Vector v2 = Nyx::Vector{1.2f, 2.1f, 3.0f};
    Nyx::Point p3 = p1 + v2;
    EXPECT_EQ(p3, (Nyx::Point{4.3f, -0.2f, 8.4f}));
    EXPECT_EQ(p3.w, 1.f);
}

TEST(Point, Subtract) {
    Nyx::Point p1 = Nyx::Point{3.1f, 2.3f, 1.0f};
    Nyx::Point p2 = Nyx::Point{1.2f, 2.1f, 3.0f};
    Nyx::Vector v3 = p1 - p2;
    EXPECT_EQ(v3, (Nyx::Vector{1.9f, 0.2f, -2.0f}));
    EXPECT_EQ(v3.w, 0.f);
}

TEST(Point, SubtractVector) {
    Nyx::Point p1 = Nyx::Point{3.1f, 2.3f, 1.0f};
    Nyx::Vector v2 = Nyx::Vector{1.2f, 2.1f, 3.0f};
    Nyx::Point p3 = p1 - v2;
    EXPECT_EQ(p3, (Nyx::Point{1.9f, 0.2f, -2.0f}));
    EXPECT_EQ(p3.w, 1.f);
}

TEST(Point, Negate) {
    Nyx::Point p1 = Nyx::Point{3.1f, -2.3f, 1.0f};
    Nyx::Point p2 = -p1;
    EXPECT_EQ(p2, (Nyx::Point{-3.1f, 2.3f, -1.0f}));
    EXPECT_EQ(p2.w, 1.f);
}
