#pragma once

#include "tuple.hpp"
#include "matrix.hpp"
#include "transformation.hpp"
#include "config.hpp"

namespace Nyx {
    struct Ray {
        Point origin;
        Vector direction;

        Ray(const Point& origin, const Vector& direction) : origin(origin), direction(direction) {}

        Point position(float t) const {
            return origin + direction * t;
        }

        Ray transform(const Matrix<4>& m) const {
            return Ray(m * origin, m * direction);
        }

        friend Ray operator*(const Transformation& t, const Ray& r) {
            return r.transform(t.matrix());
        }
    };
}