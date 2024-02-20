#pragma once

#include <array>
#include <ostream>
#include <memory>
#include "pattern.hpp"
#include "color.hpp"

namespace Nyx {
    struct Checker3DPattern : public Pattern {
        const std::array<Color, 2> cs;

        Checker3DPattern(const Color& a, const Color& b) : cs({a, b}) {}

        Color at(const Point& point) const override {
            return cs[static_cast<int>(std::abs(std::floor(point.x) + std::floor(point.y) + std::floor(point.z))) % 2];
        }

        virtual bool operator==(const std::shared_ptr<Pattern> other) const override {
            if (auto checker3DPatternPtr = std::dynamic_pointer_cast<Checker3DPattern>(other)) {
                return cs[0] == checker3DPatternPtr->cs[0] && cs[1] == checker3DPatternPtr->cs[1];
            } else {
                return false;
            }
        }

        virtual std::string to_string() const override {
            std::stringstream ss;
            ss << "Checker3DPattern(" << cs[0] << ", " << cs[1] << ")";
            return ss.str();
        }
    };
}