#pragma once

#include <array>
#include <ostream>
#include <memory>
#include "pattern.hpp"
#include "color.hpp"

namespace Nyx {
    struct GradientPattern : public Pattern {
        const Color from, to;

        GradientPattern(const Color& from, const Color& to) : from(from), to(to) {}

        Color at(const Point& point) const override {
            return from + (to - from) * (point.x - std::floor(point.x));
        }

        virtual bool operator==(const std::shared_ptr<Pattern> other) const override {
            if (auto gradientPatternPtr = std::dynamic_pointer_cast<GradientPattern>(other)) {
                return from == gradientPatternPtr->from && to == gradientPatternPtr->to;
            } else {
                return false;
            }
        }

        virtual std::string to_string() const override {
            std::stringstream ss;
            ss << "GradientPattern(" << from << ", " << to << ")";
            return ss.str();
        }
    };
}