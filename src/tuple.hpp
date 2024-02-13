#pragma once
#include <cmath>
#include <cassert>
#include <ostream>

#include "config.hpp"

namespace Nyx {
    struct Tuple {
        float x, y, z, w;

        bool operator==(const Tuple& other) const {
            return
                std::abs(x - other.x) < EPSILON &&
                std::abs(y - other.y) < EPSILON &&
                std::abs(z - other.z) < EPSILON &&
                std::abs(w - other.w) < EPSILON;
        }

        friend std::ostream& operator<<(std::ostream& os, const Tuple& t) {
            os << "Tuple(" << t.x << ", " << t.y << ", " << t.z << ", " << t.w << ")";
            return os;
        }
    };

    struct Vector : public Tuple {
        Vector(float x, float y, float z) : Tuple({x, y, z, 0.f}) {}

        Vector operator+(const Vector& v) const {
            return Vector{x + v.x, y + v.y, z + v.z};
        }

        Vector operator-(const Vector& v) const {
            return Vector{x - v.x, y - v.y, z - v.z};
        }

        Vector operator-() const {
            return Vector{-x, -y, -z};
        }

        Vector operator*(float scalar) const {
            return Vector{x * scalar, y * scalar, z * scalar};
        }

        Vector operator/(float scalar) const {
            assert(scalar != 0);
            return Vector{x / scalar, y / scalar, z / scalar};
        }

        float magnitude() const {
            return std::sqrt(x * x + y * y + z * z);
        }

        Vector normalize() const {
            return (*this) / magnitude();
        }

        float dot(const Vector& v) const {
            return x * v.x + y * v.y + z * v.z;
        }

        Vector cross(const Vector& v) const {
            return Vector{
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x
            };
        }

        Vector reflect(const Vector& normal) const {
            return *this - normal * 2.f * dot(normal);
        }
    };

    struct Point : public Tuple {
        Point(float x, float y, float z) : Tuple({x, y, z, 1.f}) {}

        Point operator+(const Vector& v) const {
            return Point{x + v.x, y + v.y, z + v.z};
        }

        Vector operator-(const Point& p) const {
            return Vector{x - p.x, y - p.y, z - p.z};
        }

        Point operator-(const Vector& v) const {
            return Point{x - v.x, y - v.y, z - v.z};
        }

        Point operator-() const {
            return Point{-x, -y, -z};
        }
    };
}
