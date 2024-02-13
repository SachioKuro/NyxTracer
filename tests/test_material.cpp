#include <gtest/gtest.h>
#include "../src/material.hpp"
#include "../src/color.hpp"
#include "../src/point_light.hpp"
#include "../src/tuple.hpp"

TEST(Material, Init) {
    Nyx::Material m = Nyx::Material();
    EXPECT_EQ(m.color, Nyx::Color(1, 1, 1));
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
    m2.color = Nyx::Color(1, 0, 0);
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
    EXPECT_EQ(result, Nyx::Color(1.6364, 1.6364, 1.6364));
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