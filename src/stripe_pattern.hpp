#pragma once

#include <array>
#include <ostream>
#include <memory>
#include "pattern.hpp"
#include "color.hpp"

namespace Nyx {
    struct StripePattern : public Pattern {
        const std::array<Color, 2> cs;

        StripePattern(const Color& a, const Color& b) : cs({a, b}) {}

        Color at(const Point& point) const override {
            return cs[static_cast<int>(std::abs(std::floor(point.x))) % 2];
        }

        virtual bool operator==(const std::shared_ptr<Pattern> other) const override {
            if (auto stripePatternPtr = std::dynamic_pointer_cast<StripePattern>(other)) {
                return cs[0] == stripePatternPtr->cs[0] && cs[1] == stripePatternPtr->cs[1];
            } else {
                return false;
            }
        }

        virtual std::string to_string() const override {
            std::stringstream ss;
            ss << "StripePattern(" << cs[0] << ", " << cs[1] << ")";
            return ss.str();
        }
    };
}