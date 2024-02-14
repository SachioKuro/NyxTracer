#pragma once

#include <ostream>
#include "tuple.hpp"	
#include "color.hpp"

namespace Nyx {
    struct PointLight {
        Point position;
        Color intensity;

        PointLight(const Point& position, const Color& intensity) : position(position), intensity(intensity) {}

        bool operator==(const PointLight& other) const {
            return position == other.position && intensity == other.intensity;
        }

        friend std::ostream& operator<<(std::ostream& os, const PointLight& l) {
            os << "PointLight(" << l.position << ", " << l.intensity << ")";
            return os;
        }
    };
}