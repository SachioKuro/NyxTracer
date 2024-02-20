#pragma once

#include <cmath>
#include <memory>
#include <ostream>
#include "point_light.hpp"
#include "color.hpp"
#include "pattern.hpp"
#include "constant_pattern.hpp"
#include "config.hpp"

namespace Nyx {
    struct Material {
        std::shared_ptr<Pattern> pattern;
        float ambient, diffuse, specular, shininess;

        Material() : pattern(std::make_shared<ConstantPattern>(Color{1.f, 1.f, 1.f})), ambient(0.1f), diffuse(0.9f), specular(0.9f), shininess(200.f) {}

        bool operator==(const Material& m) const {
            return *pattern == m.pattern &&
                std::abs(ambient - m.ambient) < EPSILON &&
                std::abs(diffuse - m.diffuse) < EPSILON &&
                std::abs(specular - m.specular) < EPSILON &&
                std::abs(shininess - m.shininess) < EPSILON;
        }

        Color lighting(
            const PointLight& light,
            const Point& position,
            const Vector& eye,
            const Vector& normal,
            const Transformation& object_transform = Transformation::identity(),
            bool inShadow = false
        ) const {
            Color effective_color = pattern->at_object(object_transform * position) * light.intensity;
            Color ambient_color = effective_color * ambient;

            if (inShadow) {
                return ambient_color;
            }
            
            Vector lightv = (light.position - position).normalize();
            float light_dot_normal = lightv.dot(normal);
            if (light_dot_normal <= 0) {
                return ambient_color;
            }
            Color diffuse_color = effective_color * diffuse * light_dot_normal;

            Vector reflectv = (-lightv).reflect(normal);
            float reflect_dot_eye = reflectv.dot(eye);
            if (reflect_dot_eye <= 0) {
                return ambient_color + diffuse_color;
            }
            float factor = std::pow(reflect_dot_eye, shininess);
            Color specular_color = light.intensity * specular * factor;

            return ambient_color + diffuse_color + specular_color;
        }

        friend std::ostream& operator<<(std::ostream& os, const Material& m) {
            os << "Material(" << *m.pattern << ", " << m.ambient << ", " << m.diffuse << ", " << m.specular << ", " << m.shininess << ")";
            return os;
        }
    };
}