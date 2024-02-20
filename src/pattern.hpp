#pragma once

#include <ostream>
#include "color.hpp"
#include "tuple.hpp"
#include "transformation.hpp"

namespace Nyx {
    struct Pattern {
        Transformation transform;

        Pattern() : transform(Transformation::identity()) {}
        virtual ~Pattern() = default;
        virtual Color at(const Point& point) const = 0;
        virtual Color at_object(const Point& point) const {
            return at(transform.inverse() * point); // TODO: pre compute inverse
        }

        virtual bool operator==(const std::shared_ptr<Pattern> other) const = 0;
        virtual std::string to_string() const = 0;

        virtual void set_transform(const Transformation& t) {
            transform = t;
        }

        friend std::ostream& operator<<(std::ostream& os, const Pattern& p) {
            os << p.to_string();
            return os;
        }
    };
}