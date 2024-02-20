#include <iostream>
#include <cmath>
#include <memory>

#include "config.hpp"
#include "bitmap.hpp"
#include "canvas.hpp"
#include "color.hpp"
#include "constant_pattern.hpp"
#include "tuple.hpp"
#include "point_light.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "transformation.hpp"
#include "world.hpp"
#include "camera.hpp"
#include "pattern.hpp"
#include "stripe_pattern.hpp"
#include "gradient_pattern.hpp"
#include "ring_pattern.hpp"
#include "checker3D_pattern.hpp"
#include "radial_gradient_pattern.hpp"

int main() {
    Nyx::World world;
    world.lights.push_back(Nyx::PointLight(Nyx::Point(-4, 10, -10), Nyx::Color(1, 1, 1)));
    //world.lights.push_back(Nyx::PointLight(Nyx::Point(5, 8, -10), Nyx::Color(0.5, 0, 0.5)));

    Nyx::Plane floor = Nyx::Plane();
    floor.material.pattern = std::make_shared<Nyx::StripePattern>(Nyx::Color(0.65, 0.65, 0.65), Nyx::Color(0.55, 0.55, 0.55));
    world.objects.push_back(&floor);

    Nyx::Plane back = Nyx::Plane();
    back.material.pattern = std::make_shared<Nyx::RadialGradientPattern>(
        Nyx::Color(0.1, 0.1, 0.1), Nyx::Color(0.9, 0.9, 0.9), Nyx::Color(0.9, 0.9, 0.9), Nyx::Color(0.1, 0.1, 0.1)
    );
    back.material.pattern->set_transform(Nyx::Transformation::identity().shear(0, 1, 0, 0, 0, 0));
    back.set_transform(Nyx::Transformation::identity().rotateX(M_PI / 2).translate(0, 0, 5));
    world.objects.push_back(&back);

    Nyx::Sphere s1 = Nyx::Sphere();
    s1.material.pattern = std::make_shared<Nyx::GradientPattern>(Nyx::Color(0, 0, 1), Nyx::Color(0, 1, 0));
    s1.material.pattern->set_transform(Nyx::Transformation::identity().scale(2.1, 1, 1).translate(-1, 0, 0).rotateZ(M_PI / 4));
    s1.set_transform(Nyx::Transformation::identity().scale(0.5, 0.5, 0.5).translate(-1, 0.5, 0));
    world.objects.push_back(&s1);

    Nyx::Sphere s2 = Nyx::Sphere();
    s2.material.pattern = std::make_shared<Nyx::StripePattern>(Nyx::Color(0.5, 0.1, 0.1), Nyx::Color(0.1, 0.5, 0.1));
    s2.material.pattern->set_transform(Nyx::Transformation::identity().scale(0.2, 0.2, 0.2));
    s2.material.diffuse = 0.7;
    s2.material.specular = 0.3;
    s2.set_transform(Nyx::Transformation::identity().scale(0.5, 0.5, 0.5).translate(0.5, 0.5, 0));
    world.objects.push_back(&s2);

    Nyx::Sphere s3 = Nyx::Sphere();
    s3.material.pattern = std::make_shared<Nyx::ConstantPattern>(Nyx::Color(0.1, 0.1, 0.1));
    s3.material.diffuse = 0.7;
    s3.material.specular = 0.8;
    s3.set_transform(Nyx::Transformation::identity().scale(0.75, 0.75, 0.75).translate(-0.15, 0.75, 1));
    world.objects.push_back(&s3);

    Nyx::Sphere s4 = Nyx::Sphere();
    s4.material.pattern = std::make_shared<Nyx::RingPattern>(Nyx::Color(0.1, 0.1, 0.1), Nyx::Color(0.9, 0.9, 0.9));
    s4.material.pattern->set_transform(Nyx::Transformation::identity().scale(0.1, 1, 0.1).translate(0.5, 0, 0.5).rotateX(M_PI / 3).rotateY(M_PI / 3));
    s4.material.diffuse = 0.7;
    s4.material.specular = 0.8;
    s4.set_transform(Nyx::Transformation::identity().scale(0.9, 0.9, 0.9).translate(2, 0.9, 2));
    world.objects.push_back(&s4);

    Nyx::Sphere s5 = Nyx::Sphere();
    s5.material.pattern = std::make_shared<Nyx::Checker3DPattern>(Nyx::Color(0.5, 0.5, 0), Nyx::Color(0.5, 0.5, 1));
    s5.material.pattern->set_transform(Nyx::Transformation::identity().scale(0.2, 0.2, 0.2).rotateZ(M_PI /6));
    s5.set_transform(Nyx::Transformation::identity().scale(0.35, 0.35, 0.35).translate(-0.5, 0.35, -0.5));
    world.objects.push_back(&s5);

    Nyx::Camera camera = Nyx::Camera(Nyx::WIDTH, Nyx::HEIGHT, M_PI / 3);
    camera.transform = Nyx::Transformation::view(Nyx::Point(0, 2, -5), Nyx::Point(0, 1, 0), Nyx::Vector(0, 1, 0));
    Nyx::Canvas canvas = camera.render(world);

    Nyx::Image::write_bitmap("sphere.bmp", canvas.pixels);

    return 0;
}