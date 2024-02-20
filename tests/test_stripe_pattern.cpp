#include <gtest/gtest.h>
#include "../src/stripe_pattern.hpp"
#include "../src/color.hpp"
#include "../src/tuple.hpp"

TEST(StripePattern, CreatingStripePattern) {
    Nyx::Color a(1, 1, 1);
    Nyx::Color b(0, 0, 0);
    Nyx::StripePattern pattern(a, b);
    ASSERT_EQ(pattern.cs[0], a);
    ASSERT_EQ(pattern.cs[1], b);
}

TEST(StripePattern, StripePatternIsConstantInY) {
    Nyx::Color a(1, 1, 1);
    Nyx::Color b(0, 0, 0);
    Nyx::StripePattern pattern(a, b);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0, 0)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 1, 0)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 2, 0)), a);
}

TEST(StripePattern, StripePatternIsConstantInZ) {
    Nyx::Color a(1, 1, 1);
    Nyx::Color b(0, 0, 0);
    Nyx::StripePattern pattern(a, b);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0, 0)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0, 1)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0, 2)), a);
}

TEST(StripePattern, StripePatternAlternatesInX) {
    Nyx::Color a(1, 1, 1);
    Nyx::Color b(0, 0, 0);
    Nyx::StripePattern pattern(a, b);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0, 0)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(0.9, 0, 0)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(1, 0, 0)), b);
    ASSERT_EQ(pattern.at(Nyx::Point(-0.1, 0, 0)), b);
    ASSERT_EQ(pattern.at(Nyx::Point(-1, 0, 0)), b);
    ASSERT_EQ(pattern.at(Nyx::Point(-1.1, 0, 0)), a);
}