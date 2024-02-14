#include "hit.hpp"

namespace Nyx {
    bool Hit::operator==(const Hit& other) const {
        return intersection == other.intersection;
    }

    Hit::operator bool() const {
        return intersection.is_valid();
    }

    Hit Hit::prepare(const Intersection& intersection, const Ray& ray) {
        Point point = ray.position(intersection.t);
        Vector eyev = -ray.direction;
        Vector normalv = intersection.object->normal_at(point);
        return Hit(intersection, point, eyev, normalv);
    }

    Hit Hit::prepare(const Ray& ray) const {
        return Hit::prepare(intersection, ray);
    }
}