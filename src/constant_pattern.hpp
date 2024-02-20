#pragma once

#include <ostream>
#include "pattern.hpp"
#include "color.hpp"

namespace Nyx {
    struct ConstantPattern : public Pattern {
        const Color c;

        ConstantPattern(const Color& c) : c(c) {}

        Color at(const Point& point) const override {
            return c;
        }

        bool operator==(const std::shared_ptr<Pattern> other) const override {
            if (auto constantPatternPtr = std::dynamic_pointer_cast<ConstantPattern>(other)) {
                return c == constantPatternPtr->c;
            } else {
                return false;
            }
        }

        std::string to_string() const override {
            std::stringstream ss;
            ss << "ConstantPattern(" << c << ")";
            return ss.str();
        }
    };
}