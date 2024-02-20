#include <gtest/gtest.h>
#include "../src/checker3D_pattern.hpp"

TEST(Checker3DPattern, CreatingThePattern) {
    Nyx::Color a = Nyx::Color(1, 1, 1);
    Nyx::Color b = Nyx::Color(0, 0, 0);
    Nyx::Checker3DPattern pattern = Nyx::Checker3DPattern(a, b);
    ASSERT_EQ(pattern.cs[0], a);
    ASSERT_EQ(pattern.cs[1], b);
}

TEST(Checker3DPattern, Checker3DPatternShouldRepeatInX) {
    Nyx::Color a = Nyx::Color(1, 1, 1);
    Nyx::Color b = Nyx::Color(0, 0, 0);
    Nyx::Checker3DPattern pattern = Nyx::Checker3DPattern(a, b);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0, 0)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(0.99, 0, 0)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(1.01, 0, 0)), b);
    ASSERT_EQ(pattern.at(Nyx::Point(-0.1, 0, 0)), b);
    ASSERT_EQ(pattern.at(Nyx::Point(-1.01, 0, 0)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(-1.1, 0, 0)), a);
}

TEST(Checker3DPattern, Checker3DPatternShouldRepeatInY) {
    Nyx::Color a = Nyx::Color(1, 1, 1);
    Nyx::Color b = Nyx::Color(0, 0, 0);
    Nyx::Checker3DPattern pattern = Nyx::Checker3DPattern(a, b);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0, 0)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0.99, 0)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 1.01, 0)), b);
    ASSERT_EQ(pattern.at(Nyx::Point(0, -0.1, 0)), b);
    ASSERT_EQ(pattern.at(Nyx::Point(0, -1.01, 0)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(0, -1.1, 0)), a);
}

TEST(Checker3DPattern, Checker3DPatternShouldRepeatInZ) {
    Nyx::Color a = Nyx::Color(1, 1, 1);
    Nyx::Color b = Nyx::Color(0, 0, 0);
    Nyx::Checker3DPattern pattern = Nyx::Checker3DPattern(a, b);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0, 0)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0, 0.99)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0, 1.01)), b);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0, -0.1)), b);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0, -1.01)), a);
    ASSERT_EQ(pattern.at(Nyx::Point(0, 0, -1.1)), a);
}