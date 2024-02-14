#pragma once

#include <cmath>
#include "transformation.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "canvas.hpp"

namespace Nyx {
    struct Camera {
        int hsize;
        int vsize;
        float aspect;
        float field_of_view;
        float half_view;
        Transformation transform;

        Camera(int hsize, int vsize, float field_of_view, const Transformation& transform)
            : hsize(hsize), vsize(vsize), aspect((float)hsize / (float)vsize),
              field_of_view(field_of_view), half_view(std::tan(field_of_view / 2)), transform(transform) {}

        Camera(int hsize, int vsize, float field_of_view)
            : hsize(hsize), vsize(vsize), aspect((float)hsize / (float)vsize),
              field_of_view(field_of_view), half_view(std::tan(field_of_view / 2)), transform(Transformation::identity()) {}

        float half_width() const;
        float half_height() const;
        float pixel_size() const;
        Ray ray_for_pixel(int x, int y) const;
        Canvas render(const World& w) const;
    };
}