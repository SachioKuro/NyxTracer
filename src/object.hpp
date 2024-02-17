#pragma once

#include <vector>
#include <ostream>
#include "material.hpp"
#include "uid.hpp"
#include "tuple.hpp"
#include "transformation.hpp"
#include "ray.hpp"

namespace Nyx {
    struct Intersection;
    struct Object {
        UID id;
    
        Transformation transform = Transformation();
        Transformation inverse_transform = transform.inverse();
        Transformation inverse_transpose_transform = transform.transpose();

        Material material = Material();

        Object() : id() {}

        bool operator==(const Object& other) const {
            return id == other.id;
        }

        bool operator!=(const Object& other) const {
            return id != other.id;
        }

        void set_transform(const Transformation& t) {
            transform = t;
            inverse_transform = t.inverse();
            inverse_transpose_transform = inverse_transform.transpose();
        }

        virtual Vector normal_at(const Point& world_point) const {
            return Vector(0, 0, 0);
        }

        virtual std::vector<Intersection> intersect(const Ray& ray) const {
            return {};
        }

        friend std::ostream& operator<<(std::ostream& os, const Object& o) {
            os << "Object(id: " << o.id.value << ")";
            return os;
        }
    };
}