#include <gtest/gtest.h>
#include "../src/ring_pattern.hpp"
#include "../src/color.hpp"
#include "../src/tuple.hpp"

TEST(RingPattern, CreatingRingPattern) {
    Nyx::Color a(1, 1, 1);
    Nyx::Color b(0, 0, 0);
    Nyx::RingPattern pattern(a, b);
    ASSERT_EQ(pattern.cs[0], a);
    ASSERT_EQ(pattern.cs[1], b);
}

TEST(RingPattern, RingPatternIsConstantInY) {
    Nyx::Color a(1, 1, 1);
    Nyx::Color b(0, 0, 0);
    Nyx::RingPattern pattern(a, b);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0, 0)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 1, 0)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 2, 0)), a);
}

TEST(RingPattern, RingPatternAlternatesInX) {
    Nyx::Color a(1, 1, 1);
    Nyx::Color b(0, 0, 0);
    Nyx::RingPattern pattern(a, b);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0, 0)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(1, 0, 0)), b);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0, 1)), b);
    ASSERT_EQ(pattern.at(Nyx::Point(0.708, 0, 0.708)), b);
}