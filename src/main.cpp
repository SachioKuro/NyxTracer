#include <iostream>
#include <cmath>

#include "config.hpp"
#include "bitmap.hpp"
#include "canvas.hpp"
#include "color.hpp"
#include "tuple.hpp"
#include "point_light.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "transformation.hpp"
#include "intersection.hpp"
#include "hit.hpp"

int main() {
    Nyx::Canvas c(Nyx::WIDTH, Nyx::HEIGHT);
    Nyx::PointLight light(Nyx::Point(-10, 10, -10), Nyx::Color(1, 1, 1));
    Nyx::Sphere s = Nyx::Sphere(Nyx::Point(0, 0, 0), 1);
    s.material.color = Nyx::Color(1, 0.2, 1);

    Nyx::Point ray_origin = Nyx::Point(0, 0, -5);
    float wall_z = 10;
    float wall_size = 10;
    float pixel_size = wall_size / Nyx::WIDTH;
    float half = wall_size / 2;

    for (int y = 0; y < Nyx::HEIGHT; y++) {
        float world_y = half - pixel_size * y;
        for (int x = 0; x < Nyx::WIDTH; x++) {
            float world_x = -half + pixel_size * x;
            Nyx::Point position = Nyx::Point(world_x, world_y, wall_z);
            Nyx::Ray r = Nyx::Ray(ray_origin, (position - ray_origin).normalize());

            auto xs = s.intersect(r);
            if (auto hit = Nyx::Intersection::hit(xs, r); hit) {
                Nyx::Vector normal = hit.normalv;
                Nyx::Vector eye = hit.eyev;
                Nyx::Color color = hit.intersection.object->material.lighting(light, position, eye, normal);
                c.write_pixel(x, y, color);
            }
        }
    }

    Nyx::Image::write_bitmap("sphere.bmp", c.pixels);

    return 0;
}