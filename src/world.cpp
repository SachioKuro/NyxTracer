#include "world.hpp"
#include "hit.hpp"

namespace Nyx {
    World World::default_world() {
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

    std::vector<Intersection> World::intersect(const Ray& ray) const {
        std::vector<Intersection> xs;
        for (const auto& object : objects) {
            auto object_xs = object->intersect(ray);
            xs.insert(xs.end(), object_xs.begin(), object_xs.end());
        }
        std::sort(xs.begin(), xs.end());
        return xs;
    }

    Color World::shade_hit(const Hit& hit) const {
        Color color = Color(0, 0, 0);
        for (const auto& light : lights) {
            bool in_shadow = is_shadowed(hit.over_point, light);
            color += hit.intersection.object->material.lighting(light, hit.over_point, hit.eyev, hit.normalv, in_shadow);
        }
        return color;
    }

    Color World::color_at(const Ray& ray) const {
        auto xs = intersect(ray);
        auto hit = Intersection::hit(xs, ray);
        if (hit) {
            return shade_hit(hit);
        }
        return Color(0, 0, 0);
    }

    bool World::is_shadowed(const Point& point, const PointLight& light) const {
        auto v = light.position - point;
        auto distance = v.magnitude();
        auto direction = v.normalize();
        auto r = Ray(point, direction);
        auto xs = intersect(r);
        auto h = Intersection::hit(xs, r);
        return h && h.intersection.t < distance;
    }

    std::ostream& operator<<(std::ostream& os, const World& w) {
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
}