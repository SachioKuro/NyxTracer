#include <gtest/gtest.h>
#include "../src/tuple.hpp"

TEST(Vector, Init) {
    Nyx::Vector v = Nyx::Vector{4.3f, -4.2f, 3.1f};
    EXPECT_FLOAT_EQ(v.x, 4.3f);
    EXPECT_FLOAT_EQ(v.y, -4.2f);
    EXPECT_FLOAT_EQ(v.z, 3.1f);
    EXPECT_FLOAT_EQ(v.w, 0.f);
}

TEST(Vector, Equal) {
    Nyx::Vector v1 = Nyx::Vector{4.3f, -4.2f, 3.1f};
    Nyx::Vector v2 = Nyx::Vector{4.3f, -4.2f, 3.1f};
    EXPECT_EQ(v1, v2);
}

TEST(Vector, Add) {
    Nyx::Vector v1 = Nyx::Vector{3.1f, -2.3f, 5.4f};
    Nyx::Vector v2 = Nyx::Vector{1.2f, 2.1f, 3.0f};
    Nyx::Vector v3 = v1 + v2;
    EXPECT_EQ(v3, (Nyx::Vector{4.3f, -0.2f, 8.4f}));
    EXPECT_EQ(v3.w, 0.f);
}

TEST(Vector, Subtract) {
    Nyx::Vector v1 = Nyx::Vector{3.1f, 2.3f, 1.0f};
    Nyx::Vector v2 = Nyx::Vector{1.2f, 2.1f, 3.0f};
    Nyx::Vector v3 = v1 - v2;
    EXPECT_EQ(v3, (Nyx::Vector{1.9f, 0.2f, -2.0f}));
    EXPECT_EQ(v3.w, 0.f);
}

TEST(Vector, Negate) {
    Nyx::Vector v1 = Nyx::Vector{3.1f, -2.3f, 1.0f};
    Nyx::Vector v2 = -v1;
    EXPECT_EQ(v2, (Nyx::Vector{-3.1f, 2.3f, -1.0f}));
    EXPECT_EQ(v2.w, 0.f);
}

TEST(Vector, Multiply) {
    Nyx::Vector v1 = Nyx::Vector{1.0f, -2.0f, 3.0f};
    Nyx::Vector v2 = v1 * 3.5f;
    EXPECT_EQ(v2, (Nyx::Vector{3.5f, -7.0f, 10.5f}));
    EXPECT_EQ(v2.w, 0.f);

    Nyx::Vector v3 = v1 * 0.5f;
    EXPECT_EQ(v3, (Nyx::Vector{0.5f, -1.0f, 1.5f}));
}

TEST(Vector, Divide) {
    Nyx::Vector v1 = Nyx::Vector{1.0f, -2.0f, 3.0f};
    Nyx::Vector v2 = v1 / 2.0f;
    EXPECT_EQ(v2, (Nyx::Vector{0.5f, -1.0f, 1.5f}));
    EXPECT_EQ(v2.w, 0.f);
}

TEST(Vector, Magnitude) {
    Nyx::Vector v1 = Nyx::Vector{1.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(v1.magnitude(), 1.f);

    Nyx::Vector v2 = Nyx::Vector{0.0f, 1.0f, 0.0f};
    EXPECT_FLOAT_EQ(v2.magnitude(), 1.f);

    Nyx::Vector v3 = Nyx::Vector{0.0f, 0.0f, 1.0f};
    EXPECT_FLOAT_EQ(v3.magnitude(), 1.f);

    Nyx::Vector v4 = Nyx::Vector{1.0f, 2.0f, 3.0f};
    EXPECT_FLOAT_EQ(v4.magnitude(), sqrt(14.f));

    Nyx::Vector v5 = Nyx::Vector{-1.0f, -2.0f, -3.0f};
    EXPECT_FLOAT_EQ(v5.magnitude(), sqrt(14.f));
}

TEST(Vector, Normalize) {
    Nyx::Vector v1 = Nyx::Vector{4.0f, 0.0f, 0.0f};
    Nyx::Vector v2 = v1.normalize();
    EXPECT_EQ(v2, (Nyx::Vector{1.0f, 0.0f, 0.0f}));

    Nyx::Vector v3 = Nyx::Vector{0.0f, 3.0f, 0.0f};
    Nyx::Vector v4 = v3.normalize();
    EXPECT_EQ(v4, (Nyx::Vector{0.0f, 1.0f, 0.0f}));

    Nyx::Vector v5 = Nyx::Vector{0.0f, 0.0f, 2.5f};
    Nyx::Vector v6 = v5.normalize();
    EXPECT_EQ(v6, (Nyx::Vector{0.0f, 0.0f, 1.0f}));

    Nyx::Vector v7 = Nyx::Vector{1.0f, 2.0f, 3.0f};
    Nyx::Vector v8 = v7.normalize();
    EXPECT_EQ(v8, (Nyx::Vector{0.26726f, 0.53452f, 0.80178f}));
    EXPECT_FLOAT_EQ(v8.magnitude(), 1.f);
}

TEST(Vector, Dot) {
    Nyx::Vector v1 = Nyx::Vector{1.0f, 2.0f, 3.0f};
    Nyx::Vector v2 = Nyx::Vector{2.0f, 3.0f, 4.0f};
    EXPECT_FLOAT_EQ(v1.dot(v2), 20.f);
}

TEST(Vector, Cross) {
    Nyx::Vector v1 = Nyx::Vector{1.0f, 2.0f, 3.0f};
    Nyx::Vector v2 = Nyx::Vector{2.0f, 3.0f, 4.0f};
    EXPECT_EQ(v1.cross(v2), (Nyx::Vector{-1.0f, 2.0f, -1.0f}));
    EXPECT_EQ(v2.cross(v1), (Nyx::Vector{1.0f, -2.0f, 1.0f}));
}

TEST(Vector, Reflect45) {
    Nyx::Vector v = Nyx::Vector{1, -1, 0};
    Nyx::Vector n = Nyx::Vector{0, 1, 0};
    Nyx::Vector r = v.reflect(n);
    EXPECT_EQ(r, (Nyx::Vector{1, 1, 0}));
}

TEST(Vector, ReflectSlanted) {
    Nyx::Vector v = Nyx::Vector{0, -1, 0};
    Nyx::Vector n = Nyx::Vector{sqrt(2)/2, sqrt(2)/2, 0};
    Nyx::Vector r = v.reflect(n);
    EXPECT_EQ(r, (Nyx::Vector{1, 0, 0}));
}