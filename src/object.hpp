#pragma once

#include "material.hpp"
#include "uid.hpp"
#include "transformation.hpp"

namespace Nyx {
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
    };
}