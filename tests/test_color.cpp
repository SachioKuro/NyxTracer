#include <gtest/gtest.h>
#include "../src/color.hpp"

TEST(Color, Init) {
    Nyx::Color c = Nyx::Color{4.3f, -4.2f, 3.1f};
    EXPECT_FLOAT_EQ(c.r, 4.3f);
    EXPECT_FLOAT_EQ(c.g, -4.2f);
    EXPECT_FLOAT_EQ(c.b, 3.1f);
}

TEST(Color, Add) {
    Nyx::Color c1 = Nyx::Color{3.1f, -2.3f, 5.4f};
    Nyx::Color c2 = Nyx::Color{1.2f, 2.1f, 3.0f};
    Nyx::Color c3 = c1 + c2;
    EXPECT_EQ(c3, (Nyx::Color{4.3f, -0.2f, 8.4f}));
}

TEST(Color, Subtract) {
    Nyx::Color c1 = Nyx::Color{3.1f, 2.3f, 1.0f};
    Nyx::Color c2 = Nyx::Color{1.2f, 2.1f, 3.0f};
    Nyx::Color c3 = c1 - c2;
    EXPECT_EQ(c3, (Nyx::Color{1.9f, 0.2f, -2.0f}));
}

TEST(Color, Multiply) {
    Nyx::Color c1 = Nyx::Color{1.0f, -2.0f, 3.0f};
    Nyx::Color c2 = c1 * 3.5f;
    EXPECT_EQ(c2, (Nyx::Color{3.5f, -7.0f, 10.5f}));

    Nyx::Color c3 = c1 * 0.5f;
    EXPECT_EQ(c3, (Nyx::Color{0.5f, -1.0f, 1.5f}));
}

TEST(Color, MultiplyColor) {
    Nyx::Color c1 = Nyx::Color{1.0f, 0.2f, 0.4f};
    Nyx::Color c2 = Nyx::Color{0.9f, 1.5f, 0.1f};
    Nyx::Color c3 = c1 * c2;
    EXPECT_EQ(c3, (Nyx::Color{0.9f, 0.3f, 0.04f}));
}

TEST(Color, Equality) {
    Nyx::Color c1 = Nyx::Color{1.0f, 0.2f, 0.4f};
    Nyx::Color c2 = Nyx::Color{1.0f, 0.2f, 0.4f};
    Nyx::Color c3 = Nyx::Color{0.9f, 1.5f, 0.1f};
    EXPECT_EQ(c1, c2);
    EXPECT_NE(c1, c3);
}

TEST(Color, ToBytes) {
    Nyx::Color c1 = Nyx::Color{1.0f, 0.2f, 0.4f};
    Nyx::Color c2 = Nyx::Color{0.9f, 1.5f, 0.1f};
    Nyx::Color c3 = Nyx::Color{0.0f, 0.0f, 0.0f};
    Nyx::Color c4 = Nyx::Color{1.0f, 1.0f, 1.0f};
    Nyx::Color c5 = Nyx::Color{0.5f, -0.5f, 1.5f};
    EXPECT_EQ(c1.to_byte(), (Nyx::ByteColor{255, 51, 102}));
    EXPECT_EQ(c2.to_byte(), (Nyx::ByteColor{229, 255, 25}));
    EXPECT_EQ(c3.to_byte(), (Nyx::ByteColor{0, 0, 0}));
    EXPECT_EQ(static_cast<Nyx::ByteColor>(c4), (Nyx::ByteColor{255, 255, 255}));
    EXPECT_EQ(static_cast<Nyx::ByteColor>(c5), (Nyx::ByteColor{127, 0, 255}));

    EXPECT_EQ(sizeof(c1.to_byte()), 3);
}