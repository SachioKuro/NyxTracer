#include <gtest/gtest.h>
#include "../src/material.hpp"
#include "../src/color.hpp"
#include "../src/point_light.hpp"
#include "../src/tuple.hpp"
#include "../src/constant_pattern.hpp"
#include "../src/stripe_pattern.hpp"
#include "../src/transformation.hpp"

TEST(Material, Init) {
    Nyx::Material m = Nyx::Material();
    EXPECT_EQ(m.pattern, Nyx::ConstantPattern({1, 1, 1}));
    EXPECT_FLOAT_EQ(m.ambient, 0.1);
    EXPECT_FLOAT_EQ(m.diffuse, 0.9);
    EXPECT_FLOAT_EQ(m.specular, 0.9);
    EXPECT_FLOAT_EQ(m.shininess, 200);
}

TEST(Material, Equal) {
    Nyx::Material m1 = Nyx::Material();
    Nyx::Material m2 = Nyx::Material();
    EXPECT_EQ(m1, m2);
}

TEST(Material, NotEqual) {
    Nyx::Material m1 = Nyx::Material();
    Nyx::Material m2 = Nyx::Material();
    m2.pattern = std::make_shared<Nyx::StripePattern>(Nyx::Color(1, 1, 1), Nyx::Color(0, 0, 0));
    EXPECT_NE(m1, m2);
}

TEST(Material, NotEqualAmbient) {
    Nyx::Material m1 = Nyx::Material();
    Nyx::Material m2 = Nyx::Material();
    m2.ambient = 0.2;
    EXPECT_NE(m1, m2);
}

TEST(Material, NotEqualDiffuse) {
    Nyx::Material m1 = Nyx::Material();
    Nyx::Material m2 = Nyx::Material();
    m2.diffuse = 0.2;
    EXPECT_NE(m1, m2);
}

TEST(Material, NotEqualSpecular) {
    Nyx::Material m1 = Nyx::Material();
    Nyx::Material m2 = Nyx::Material();
    m2.specular = 0.2;
    EXPECT_NE(m1, m2);
}

TEST(Material, NotEqualShininess) {
    Nyx::Material m1 = Nyx::Material();
    Nyx::Material m2 = Nyx::Material();
    m2.shininess = 300;
    EXPECT_NE(m1, m2);
}

TEST(Material, LightingEyeBetweenLightAndSurface) {
    Nyx::Material m = Nyx::Material();
    Nyx::Point position = Nyx::Point(0, 0, 0);
    Nyx::Vector eye = Nyx::Vector(0, 0, -1);
    Nyx::Vector normal = Nyx::Vector(0, 0, -1);
    Nyx::PointLight light = Nyx::PointLight(Nyx::Point(0, 0, -10), Nyx::Color(1, 1, 1));
    Nyx::Color result = m.lighting(light, position, eye, normal);
    EXPECT_EQ(result, Nyx::Color(1.9, 1.9, 1.9));
}

TEST(Material, LightingEyeBetweenLightAndSurfaceInShadow) {
    Nyx::Material m = Nyx::Material();
    Nyx::Point position = Nyx::Point(0, 0, 0);
    Nyx::Vector eye = Nyx::Vector(0, 0, -1);
    Nyx::Vector normal = Nyx::Vector(0, 0, -1);
    Nyx::PointLight light = Nyx::PointLight(Nyx::Point(0, 0, -10), Nyx::Color(1, 1, 1));
    Nyx::Color result = m.lighting(light, position, eye, normal, Nyx::Transformation::identity(), true);
    EXPECT_EQ(result, Nyx::Color(0.1, 0.1, 0.1));
}

TEST(Material, LightingEyeOffset45) {
    Nyx::Material m = Nyx::Material();
    Nyx::Point position = Nyx::Point(0, 0, 0);
    Nyx::Vector eye = Nyx::Vector(0, sqrt(2)/2, -sqrt(2)/2);
    Nyx::Vector normal = Nyx::Vector(0, 0, -1);
    Nyx::PointLight light = Nyx::PointLight(Nyx::Point(0, 0, -10), Nyx::Color(1, 1, 1));
    Nyx::Color result = m.lighting(light, position, eye, normal);
    EXPECT_EQ(result, Nyx::Color(1.0, 1.0, 1.0));
}

TEST(Material, LightingEyeOppositeSurfaceLightOffset45) {
    Nyx::Material m = Nyx::Material();
    Nyx::Point position = Nyx::Point(0, 0, 0);
    Nyx::Vector eye = Nyx::Vector(0, 0, -1);
    Nyx::Vector normal = Nyx::Vector(0, 0, -1);
    Nyx::PointLight light = Nyx::PointLight(Nyx::Point(0, 10, -10), Nyx::Color(1, 1, 1));
    Nyx::Color result = m.lighting(light, position, eye, normal);
    EXPECT_EQ(result, Nyx::Color(0.7364, 0.7364, 0.7364));
}

TEST(Material, LightingEyeInPathOfReflectionVector) {
    Nyx::Material m = Nyx::Material();
    Nyx::Point position = Nyx::Point(0, 0, 0);
    Nyx::Vector eye = Nyx::Vector(0, -sqrt(2)/2, -sqrt(2)/2);
    Nyx::Vector normal = Nyx::Vector(0, 0, -1);
    Nyx::PointLight light = Nyx::PointLight(Nyx::Point(0, 10, -10), Nyx::Color(1, 1, 1));
    Nyx::Color result = m.lighting(light, position, eye, normal);
    EXPECT_EQ(result, Nyx::Color(1.63639, 1.63639, 1.63639));
}

TEST(Material, LightingLightBehindSurface) {
    Nyx::Material m = Nyx::Material();
    Nyx::Point position = Nyx::Point(0, 0, 0);
    Nyx::Vector eye = Nyx::Vector(0, 0, -1);
    Nyx::Vector normal = Nyx::Vector(0, 0, -1);
    Nyx::PointLight light = Nyx::PointLight(Nyx::Point(0, 0, 10), Nyx::Color(1, 1, 1));
    Nyx::Color result = m.lighting(light, position, eye, normal);
    EXPECT_EQ(result, Nyx::Color(0.1, 0.1, 0.1));
}

TEST(Material, LightingWithPattern) {
    Nyx::Material m = Nyx::Material();
    m.pattern = std::make_shared<Nyx::StripePattern>(Nyx::Color(1, 1, 1), Nyx::Color(0, 0, 0));
    m.ambient = 1;
    m.diffuse = 0;
    m.specular = 0;
    Nyx::Point position = Nyx::Point(0, 0, 0);
    Nyx::Vector eye = Nyx::Vector(0, 0, -1);
    Nyx::Vector normal = Nyx::Vector(0, 0, -1);
    Nyx::PointLight light = Nyx::PointLight(Nyx::Point(0, 0, -10), Nyx::Color(1, 1, 1));
    Nyx::Color c1 = m.lighting(light, Nyx::Point(0.9, 0, 0), eye, normal);
    Nyx::Color c2 = m.lighting(light, Nyx::Point(1, 0, 0), eye, normal);
    Nyx::Color c3 = m.lighting(light, Nyx::Point(1.1, 0, 0), eye, normal);
    EXPECT_EQ(c1, Nyx::Color(1, 1, 1));
    EXPECT_EQ(c2, Nyx::Color(0, 0, 0));
    EXPECT_EQ(c3, Nyx::Color(0, 0, 0));
}