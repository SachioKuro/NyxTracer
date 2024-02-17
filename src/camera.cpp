#include "camera.hpp"

namespace Nyx {
    float Camera::half_width() const {
        if (aspect >= 1) {
            return half_view;
        } else {
            return half_view * aspect;
        }
    }

    float Camera::half_height() const {
        if (aspect >= 1) {
            return half_view / aspect;
        } else {
            return half_view;
        }
    }

    float Camera::pixel_size() const {
        return (half_width() * 2) / hsize;
    }

    Ray Camera::ray_for_pixel(int x, int y) const {
        float xoffset = (x + 0.5) * pixel_size();
        float yoffset = (y + 0.5) * pixel_size();
        float world_x = half_width() - xoffset;
        float world_y = half_height() - yoffset;
        Transformation inv_transform = transform.inverse();
        Point pixel = inv_transform * Point(world_x, world_y, -1);
        Point origin = inv_transform * Point(0, 0, 0);
        Vector direction = (pixel - origin).normalize();
        return Ray(origin, direction);
    }

    Canvas Camera::render(const World& w) const {
        Canvas image(hsize, vsize);
        for (int y = 0; y < vsize; y++) {
            for (int x = 0; x < hsize; x++) {
                Ray r = ray_for_pixel(x, y);
                Color color = w.color_at(r);
                image.write_pixel(x, y, color);
            }
        }
        return image;
    }
}