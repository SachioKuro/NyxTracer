#pragma once

#include <vector>
#include <ostream>
#include "color.hpp"
#include "transformation.hpp"
#include "object.hpp"
#include "sphere.hpp"
#include "point_light.hpp"

namespace Nyx {
    struct World {
        std::vector<Object*> objects;
        std::vector<PointLight> lights;

        World() : objects(), lights() {}

        static World default_world();

        std::vector<Intersection> intersect(const Ray& ray) const;

        Color shade_hit(const Hit& hit) const;

        Color color_at(const Ray& ray) const;

        bool is_shadowed(const Point& point, const PointLight& light) const;

        friend std::ostream& operator<<(std::ostream& os, const World& w);
    };
}