#pragma once

#include "tuple.hpp"	
#include "color.hpp"

namespace Nyx {
    struct PointLight {
        Point position;
        Color intensity;

        PointLight(const Point& position, const Color& intensity) : position(position), intensity(intensity) {}
    };
}