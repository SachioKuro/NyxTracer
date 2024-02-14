#pragma once

#include <algorithm>
#include <iomanip>
#include <ostream>
#include <cmath>

#include "config.hpp"

namespace Nyx {
    struct ByteColor {
        unsigned char r, g, b;

        bool operator==(const ByteColor& c) const {
            return r == c.r && g == c.g && b == c.b;
        }

        friend std::ostream& operator<<(std::ostream& os, const ByteColor& c) {
            os << "ByteColor(" << static_cast<int>(c.r) << ", " << static_cast<int>(c.g) << ", " << static_cast<int>(c.b) << ")";
            return os;
        }
    };

    struct Color {
        float r, g, b;

        bool operator==(const Color& c) const {
            return
                std::abs(r - c.r) < EPSILON &&
                std::abs(g - c.g) < EPSILON &&
                std::abs(b - c.b) < EPSILON;
        }

        Color operator+(const Color& c) const {
            return Color{r + c.r, g + c.g, b + c.b};
        }

        Color operator+=(const Color& c) {
            r += c.r;
            g += c.g;
            b += c.b;
            return *this;
        }

        Color operator-(const Color& c) const {
            return Color{r - c.r, g - c.g, b - c.b};
        }

        Color operator*(float scalar) const {
            return Color{r * scalar, g * scalar, b * scalar};
        }

        Color operator*(const Color& c) const {
            return Color{r * c.r, g * c.g, b * c.b};
        }

        ByteColor to_byte() const {
            return ByteColor{
                static_cast<unsigned char>(std::clamp(r, 0.f, 1.f) * 255),
                static_cast<unsigned char>(std::clamp(g, 0.f, 1.f) * 255),
                static_cast<unsigned char>(std::clamp(b, 0.f, 1.f) * 255)
            };
        }

        operator ByteColor() const {
            return to_byte();
        }

        friend std::ostream& operator<<(std::ostream& os, const Color& c) {
            os << std::fixed << std::setprecision(3)
                << "Color(" << c.r << ", " << c.g << ", " << c.b << ")";
            return os;
        }
    };
}