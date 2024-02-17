#pragma once

#include <vector>
#include "config.hpp"
#include "object.hpp"
#include "intersection.hpp"
#include "ray.hpp"
#include "tuple.hpp"

namespace Nyx {
    struct Plane : public Object {
        virtual std::vector<Intersection> intersect(const Ray& ray) const override {
            Ray rayOS = this->inverse_transform * ray;
            if (fabs(rayOS.direction.y) < EPSILON) {
                return {};
            }
            float t = -rayOS.origin.y / rayOS.direction.y;
            return {Intersection(t, this)};
        }

        virtual Vector normal_at(const Point& world_point) const override {
            return Vector(0, 1, 0);
        }
    };
}
