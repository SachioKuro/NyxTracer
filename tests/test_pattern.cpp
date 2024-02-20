#include <gtest/gtest.h>
#include "../src/stripe_pattern.hpp"
#include "../src/sphere.hpp"
#include "../src/transformation.hpp"

TEST(Pattern, StripeWithObjectTransformation) {
    Nyx::StripePattern pattern = Nyx::StripePattern(Nyx::Color(1, 1, 1), Nyx::Color(0, 0, 0));
    Nyx::Sphere s = Nyx::Sphere();
    s.set_transform(Nyx::Transformation::identity().scale(2, 2, 2));
    s.material.pattern = std::make_shared<Nyx::StripePattern>(pattern);
    Nyx::Color c = s.material.pattern->at_object(Nyx::Point(1.5, 0, 0));
    EXPECT_EQ(c, Nyx::Color(1, 1, 1));
}

TEST(Pattern, StripeWithPatternTransformation) {
    Nyx::StripePattern pattern = Nyx::StripePattern(Nyx::Color(1, 1, 1), Nyx::Color(0, 0, 0));
    Nyx::Sphere s = Nyx::Sphere();
    s.material.pattern = std::make_shared<Nyx::StripePattern>(pattern);
    s.material.pattern->set_transform(Nyx::Transformation::identity().scale(2, 2, 2));
    Nyx::Color c = s.material.pattern->at_object(Nyx::Point(1.5, 0, 0));
    EXPECT_EQ(c, Nyx::Color(1, 1, 1));
}

TEST(Pattern, StripeWithObjectAndPatternTransformation) {
    Nyx::StripePattern pattern = Nyx::StripePattern(Nyx::Color(1, 1, 1), Nyx::Color(0, 0, 0));
    Nyx::Sphere s = Nyx::Sphere();
    s.set_transform(Nyx::Transformation::identity().scale(2, 2, 2));
    s.material.pattern = std::make_shared<Nyx::StripePattern>(pattern);
    s.material.pattern->set_transform(Nyx::Transformation::identity().translate(0.5, 0, 0));
    Nyx::Color c = s.material.pattern->at_object(Nyx::Point(2.5, 0, 0));
    EXPECT_EQ(c, Nyx::Color(1, 1, 1));
}