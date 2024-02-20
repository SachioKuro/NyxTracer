#pragma once

#include <array>
#include <ostream>
#include <memory>
#include "pattern.hpp"
#include "color.hpp"

namespace Nyx {
    struct RingPattern : public Pattern {
        const std::array<Color, 2> cs;

        RingPattern(const Color& a, const Color& b) : cs({a, b}) {}

        Color at(const Point& point) const override {
            return cs[static_cast<int>(std::abs(std::floor(std::sqrt(point.x * point.x + point.z * point.z)))) % 2];
        }

        virtual bool operator==(const std::shared_ptr<Pattern> other) const override {
            if (auto ringPatternPtr = std::dynamic_pointer_cast<RingPattern>(other)) {
                return cs[0] == ringPatternPtr->cs[0] && cs[1] == ringPatternPtr->cs[1];
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