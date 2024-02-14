#pragma once

#include <algorithm>
#include <vector>

#include "config.hpp"
#include "tuple.hpp"
#include "ray.hpp"
#include "object.hpp"

namespace Nyx {
    struct Hit;
    struct Intersection {
        float t;
        const Object* object;

        Intersection(float t, const Object* object) : t(t), object(object) {}

        bool operator==(const Intersection& other) const;
        bool operator!=(const Intersection& other) const;
        bool operator<(const Intersection& other) const;

        static Hit hit(std::vector<Intersection>& intersections, const Ray& ray);

        bool is_valid() const;
        operator bool() const;
    };
}