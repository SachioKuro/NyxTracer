#include "hit.hpp"

#include "config.hpp"

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
        bool inside = false;
        if (normalv.dot(eyev) < 0) {
            inside = true;
            normalv = -normalv;
        }
        Point over_point = point + normalv * EPSILON * 5;
        return Hit(intersection, point, over_point, eyev, normalv, inside);
    }

    Hit Hit::prepare(const Ray& ray) const {
        return Hit::prepare(intersection, ray);
    }
}