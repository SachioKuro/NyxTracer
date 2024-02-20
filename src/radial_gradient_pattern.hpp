#pragma once

#include <array>
#include <ostream>
#include <memory>
#include "pattern.hpp"
#include "ring_pattern.hpp"
#include "gradient_pattern.hpp"
#include "color.hpp"

namespace Nyx {
    struct RadialGradientPattern : public Pattern {
        const std::array<Color, 2> froms;
        const std::array<Color, 2> tos;

        RadialGradientPattern(const Color& from_a, const Color& to_a, const Color& from_b, const Color& to_b)
            : froms({from_a, from_b}), tos({to_a, to_b}) {}

        Color at(const Point& point) const override {
            auto n = std::sqrt(point.x * point.x + point.z * point.z);
            auto idx = static_cast<int>(std::abs(std::floor(n))) % 2;
            Color from = froms[idx];
            Color to = tos[idx];
            return from + (to - from) * (n - std::floor(n));
        }

        Color at2(const Point& point) const {
            auto n = std::sqrt(point.x * point.x + point.z * point.z);
            auto idx = static_cast<int>(std::abs(std::floor(n))) % 2;
            Color from = froms[idx];
            Color to = tos[idx];
            return from + (to - from) * (n - std::floor(n));
        }

        virtual bool operator==(const std::shared_ptr<Pattern> other) const override {
            if (auto radialGradientPatternPtr = std::dynamic_pointer_cast<RadialGradientPattern>(other)) {
                return froms[0] == radialGradientPatternPtr->froms[0] && froms[1] == radialGradientPatternPtr->froms[1] && 
                    tos[0] == radialGradientPatternPtr->tos[0] && tos[1] == radialGradientPatternPtr->tos[1];
            } else {
                return false;
            }
        }

        virtual std::string to_string() const override {
            std::stringstream ss;
            ss << "RadialGradientPattern(" << froms[0] << ", " << tos[0] << ", " << froms[1] << ", " << tos[1] << ")";
            return ss.str();
        }

    };
}