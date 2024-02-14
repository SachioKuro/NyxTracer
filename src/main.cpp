#include <iostream>
#include <cmath>

#include "config.hpp"
#include "bitmap.hpp"
#include "canvas.hpp"
#include "color.hpp"
#include "tuple.hpp"
#include "point_light.hpp"
#include "sphere.hpp"
#include "transformation.hpp"
#include "world.hpp"
#include "camera.hpp"

int main() {
    Nyx::World world;
    world.lights.push_back(Nyx::PointLight(Nyx::Point(-4, 10, -10), Nyx::Color(1, 1, 1)));
    //world.lights.push_back(Nyx::PointLight(Nyx::Point(5, 8, -10), Nyx::Color(1, 0, 0)));

    Nyx::Sphere left_wall = Nyx::Sphere();
    left_wall.material.color = Nyx::Color(0.9, 0.9, 1);
    left_wall.set_transform(Nyx::Transformation::identity().scale(10, 0.005, 10).rotateX(M_PI / 2).rotateY(-M_PI / 4).translate(0, 0, 5));
    world.objects.push_back(&left_wall);

    Nyx::Sphere right_wall = Nyx::Sphere();
    right_wall.material.color = Nyx::Color(0.9, 0.9, 1);
    right_wall.set_transform(Nyx::Transformation::identity().scale(10, 0.005, 10).rotateX(M_PI / 2).rotateY(M_PI / 4).translate(0, 0, 5));
    world.objects.push_back(&right_wall);

    Nyx::Sphere floor = Nyx::Sphere();
    floor.material.color = Nyx::Color(0.9, 0.9, 0.9);
    floor.set_transform(Nyx::Transformation::identity().scale(10, 0.005, 10).translate(0, 0, 5));
    world.objects.push_back(&floor);

    Nyx::Sphere s1 = Nyx::Sphere();
    s1.material.color = Nyx::Color(0.1, 1, 1);
    s1.set_transform(Nyx::Transformation::identity().scale(0.5, 0.5, 0.5).translate(-1, 0.5, 0));
    world.objects.push_back(&s1);

    Nyx::Sphere s2 = Nyx::Sphere();
    s2.material.color = Nyx::Color(0.1, 1, 0.1);
    s2.material.diffuse = 0.7;
    s2.material.specular = 0.3;
    s2.set_transform(Nyx::Transformation::identity().scale(0.5, 0.5, 0.5).translate(0.5, 0.5, 0));
    world.objects.push_back(&s2);

    Nyx::Sphere s3 = Nyx::Sphere();
    s3.material.color = Nyx::Color(0.1, 0.1, 0.1);
    s3.material.diffuse = 0.7;
    s3.material.specular = 0.8;
    s3.set_transform(Nyx::Transformation::identity().scale(0.75, 0.75, 0.75).translate(-0.15, 0.75, 1));
    world.objects.push_back(&s3);

    Nyx::Camera camera = Nyx::Camera(Nyx::WIDTH, Nyx::HEIGHT, M_PI / 3);
    camera.transform = Nyx::Transformation::view(Nyx::Point(0, 2, -5), Nyx::Point(0, 1, 0), Nyx::Vector(0, 1, 0));
    Nyx::Canvas canvas = camera.render(world);

    Nyx::Image::write_bitmap("sphere.bmp", canvas.pixels);

    return 0;
}