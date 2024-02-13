#pragma once

#include <algorithm>
#include <vector>

#include "config.hpp"
#include "tuple.hpp"
#include "object.hpp"

namespace Nyx {
    struct Intersection {
        float t;
        const Object* object;

        Intersection(float t, const Object* object) : t(t), object(object) {}

        bool operator==(const Intersection& other) const {
            return t == other.t && object == other.object;
        }

        bool operator!=(const Intersection& other) const {
            return t != other.t || object != other.object;
        }

        bool operator<(const Intersection& other) const {
            return t < other.t;
        }

        static Intersection hit(std::vector<Intersection>& intersections) {
            std::sort(intersections.begin(), intersections.end());
            for (const auto& i : intersections) {
                if (i.t >= 0) {
                    return i;
                }
            }
            return Intersection(0, nullptr);
        }

        bool is_valid() const {
            return object != nullptr;
        }

        operator bool() const {
            return is_valid();
        }
    };
}