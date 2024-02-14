#pragma once

#include "intersection.hpp"
#include "tuple.hpp"

namespace Nyx {
    struct Hit {
        Intersection intersection;
        Point point;
        Vector eyev;
        Vector normalv;

        Hit(const Intersection& intersection, const Point& point, const Vector& eyev, const Vector& normalv)
            : intersection(intersection), point(point), eyev(eyev), normalv(normalv) {}

        Hit(const Intersection& intersection, const Ray& ray)
            : Hit(prepare(intersection, ray)) {}

        Hit(const Intersection& intersection) : Hit(intersection, Point(0, 0, 0), Vector(0, 0, 0), Vector(0, 0, 0)) {}

        bool operator==(const Hit& other) const;

        operator bool() const;

        static Hit prepare(const Intersection& intersection, const Ray& ray);
        Hit prepare(const Ray& ray) const;
    };
}
