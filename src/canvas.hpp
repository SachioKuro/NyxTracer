#pragma once
#include "color.hpp"

namespace Nyx {
    struct Canvas {
        int width, height;
        Color *pixels;

        Canvas(int w, int h) : width(w), height(h) {
            pixels = new Color[w * h];
            for (int i = 0; i < w * h; i++) {
                pixels[i] = Color{0.f, 0.f, 0.f};
            }
        }

        ~Canvas() {
            delete[] pixels;
        }

        void write_pixel(int x, int y, Color c) {
            pixels[x + y * width] = c;
        }

        Color& pixel_at(int x, int y) {
            return pixels[x + y * width];
        }

        Color& operator()(int x, int y) {
            return this->pixel_at(x, y);
        }
    };
}