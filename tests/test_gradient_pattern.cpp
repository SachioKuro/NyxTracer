#include <gtest/gtest.h>
#include "../src/gradient_pattern.hpp"

TEST(GradientPattern, CreatingGradientPattern) {
    Nyx::Color a(1, 1, 1);
    Nyx::Color b(0, 0, 0);
    Nyx::GradientPattern pattern(a, b);
    ASSERT_EQ(pattern.from, a);
    ASSERT_EQ(pattern.to, b);
}

TEST(GradientPattern, LinearlyInterpolatesBetweenColors) {
    Nyx::Color a(1, 1, 1);
    Nyx::Color b(0, 0, 0);
    Nyx::GradientPattern pattern(a, b);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0, 0)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(0.25, 0, 0)), Nyx::Color(0.75, 0.75, 0.75));
    ASSERT_EQ(pattern.at(Nyx::Point(0.5, 0, 0)), Nyx::Color(0.5, 0.5, 0.5));
    ASSERT_EQ(pattern.at(Nyx::Point(0.75, 0, 0)), Nyx::Color(0.25, 0.25, 0.25));
}