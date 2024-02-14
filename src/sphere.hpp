#pragma once

#include <vector>
#include "object.hpp"
#include "intersection.hpp"
#include "ray.hpp"
#include "tuple.hpp"

namespace Nyx {
    struct Sphere : public Object {
        Point center;
        float radius;

        Sphere(const Point& center, float radius) : center(center), radius(radius) {}
        Sphere() : center(Point(0, 0, 0)), radius(1) {}

        virtual std::vector<Intersection> intersect(const Ray& ray) const override {
            Ray rayOS = this->inverse_transform * ray;
            Vector sphere_to_ray = rayOS.origin - center;
            float a = rayOS.direction.dot(rayOS.direction);
            float b = 2 * rayOS.direction.dot(sphere_to_ray);
            float c = sphere_to_ray.dot(sphere_to_ray) - 1;
            float discriminant = b * b - 4 * a * c;

            if (discriminant < 0) {
                return {};
            }

            float t1 = (-b - sqrt(discriminant)) / (2 * a);
            float t2 = (-b + sqrt(discriminant)) / (2 * a);

            if (t1 > t2) {
                std::swap(t1, t2);
            }

            return {
                Intersection(t1, this),
                Intersection(t2, this)
            };
        }

        virtual Vector normal_at(const Point& world_point) const override {
            Point object_point = this->inverse_transform * world_point;
            Vector object_normal = object_point - Point(0, 0, 0);
            Vector world_normal = this->inverse_transpose_transform * object_normal;
            world_normal.w = 0;
            return world_normal.normalize();
        }
    };
}