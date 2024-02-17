#include <gtest/gtest.h>

#include "../src/camera.hpp"
#include "../src/world.hpp"
#include "../src/canvas.hpp"

TEST(Camera, Init) {
    Nyx::Camera c = Nyx::Camera(160, 120, M_PI / 2);
    EXPECT_EQ(c.hsize, 160);
    EXPECT_EQ(c.vsize, 120);
    EXPECT_FLOAT_EQ(c.field_of_view, M_PI / 2);
    EXPECT_EQ(c.transform, Nyx::Transformation::identity());
}

TEST(Camera, PixelSizeHorizontal) {
    Nyx::Camera c = Nyx::Camera(200, 125, M_PI / 2);
    EXPECT_FLOAT_EQ(c.pixel_size(), 0.01);
}

TEST(Camera, PixelSizeVertical) {
    Nyx::Camera c = Nyx::Camera(125, 200, M_PI / 2);
    EXPECT_FLOAT_EQ(c.pixel_size(), 0.01);
}

TEST(Camera, RayForPixel) {
    Nyx::Camera c = Nyx::Camera(201, 101, M_PI / 2);
    Nyx::Ray r = c.ray_for_pixel(100, 50);
    EXPECT_EQ(r.origin, Nyx::Point(0, 0, 0));
    EXPECT_EQ(r.direction, Nyx::Vector(0, 0, -1));
}

TEST(Camera, RayForPixelCorner) {
    Nyx::Camera c = Nyx::Camera(201, 101, M_PI / 2);
    Nyx::Ray r = c.ray_for_pixel(0, 0);
    EXPECT_EQ(r.origin, Nyx::Point(0, 0, 0));
    EXPECT_EQ(r.direction, Nyx::Vector(0.66519, 0.33259, -0.66851));
}

TEST(Camera, RayForPixelTransformed) {
    Nyx::Camera c = Nyx::Camera(201, 101, M_PI / 2, Nyx::Transformation::identity().translate(0, -2, 5).rotateY(M_PI / 4));
    Nyx:: Ray r = c.ray_for_pixel(100, 50);
    EXPECT_EQ(r.origin, Nyx::Point(0, 2, -5));
    EXPECT_EQ(r.direction, Nyx::Vector(std::sqrt(2) / 2, 0, -std::sqrt(2) / 2));
}

TEST(Camera, Render) {
    Nyx::World w = Nyx::World::default_world();
    Nyx::Transformation t = Nyx::Transformation::view(Nyx::Point(0, 0, -5), Nyx::Point(0, 0, 0), Nyx::Vector(0, 1, 0));
    Nyx::Camera c = Nyx::Camera(11, 11, M_PI / 2, t);
    Nyx::Canvas image = c.render(w);
    EXPECT_EQ(image.pixel_at(5, 5), Nyx::Color(0.38066, 0.47583, 0.2855));
}
