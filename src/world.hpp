#pragma once

#include <vector>
#include <ostream>
#include "transformation.hpp"
#include "object.hpp"
#include "sphere.hpp"
#include "point_light.hpp"

namespace Nyx {
    struct World {
        std::vector<Object*> objects;
        std::vector<PointLight> lights;

        World() : objects(), lights() {}
        ~World() {
            for (auto object : objects) {
                delete object;
            }
        }

        static World default_world() {
            World w = World();
            w.lights.push_back(PointLight(Point(-10, 10, -10), Color(1, 1, 1)));
            Sphere* s1 = new Sphere();
            s1->material.color = Color(0.8, 1.0, 0.6);
            s1->material.diffuse = 0.7;
            s1->material.specular = 0.2;
            w.objects.push_back(s1);
            Sphere* s2 = new Sphere();
            s2->set_transform(Transformation::identity().scale(0.5, 0.5, 0.5));
            w.objects.push_back(s2);
            return w;
        }

        std::vector<Intersection> intersect(const Ray& ray) const {
            std::vector<Intersection> xs;
            for (const auto& object : objects) {
                auto object_xs = object->intersect(ray);
                xs.insert(xs.end(), object_xs.begin(), object_xs.end());
            }
            std::sort(xs.begin(), xs.end());
            return xs;
        }

        friend std::ostream& operator<<(std::ostream& os, const World& w) {
            os << "World(objects: " << w.objects.size() << ", lights: " << w.lights.size() << ")\n";
            for (const auto& object : w.objects) {
                os << object << " ";
            }
            os << "\n";
            for (const auto& light : w.lights) {
                os << light << " ";
            }
            return os;
        }
    };
}