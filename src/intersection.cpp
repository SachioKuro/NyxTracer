#include "intersection.hpp"
#include "hit.hpp"

namespace Nyx {
    bool Intersection::operator==(const Intersection& other) const {
        return t == other.t && object == other.object;
    }

    bool Intersection::operator!=(const Intersection& other) const {
        return t != other.t || object != other.object;
    }

    bool Intersection::operator<(const Intersection& other) const {
        return t < other.t;
    }

    Hit Intersection::hit(std::vector<Intersection>& intersections, const Ray& ray) {
        std::sort(intersections.begin(), intersections.end());
        for (const auto& i : intersections) {
            if (i.t >= 0) {
                return Hit(i, ray);
            }
        }
        return Hit(Intersection(0, nullptr));
    }

    bool Intersection::is_valid() const {
        return object != nullptr;
    }

    Intersection::operator bool() const {
        return is_valid();
    }
}