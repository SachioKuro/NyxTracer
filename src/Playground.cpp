// NyxTracer.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <optional>
#include <map>

#include "common/UUID.hpp"
#include "graphics/Transformation.hpp"
#include "graphics/Canvas.hpp"
#include "graphics/Material.hpp"
#include "graphics/Light.hpp"
#include "graphics/Color.hpp"
#include "graphics/Matrix.hpp"
#include "graphics/Sphere.hpp"
#include "graphics/Ray.hpp"

int main()
{
	Canvas canvas(500, 500);

	std::map<uuid64, Sphere> spheres{};

	Sphere sphere;
	sphere.material = BasicMaterial(Color(1, 0, 0.6), .1, .9, .9, 200);
	sphere.transform = Transformation().scale(200, 200, 1).toMatrix();
	spheres[sphere.getUUID()] = sphere;

	PointLight pointLight(Point(200, 100, -1), Color(1, 1, 1));

	for (auto row = 0; row < 500; ++row) {
		for (auto col = 0; col < 500; ++col) {
			Ray ray(Point(0, 0, -2), Vector(row - 250, col - 250, 1).normalize());

			std::optional<Intersection> hit = sphere.intersect(ray).hit();

			if (hit.has_value()) {
				Sphere s = spheres[hit->obj];
				Point position = ray.position(hit->t);
				Vector normal = s.normalAt(position);
				Vector eye = -ray.direction;

				canvas(row, col) = s.material.lighting(pointLight, position, eye, normal);
			}
		}
	}

	std::ofstream ofs;
	ofs.open("C:\\Users\\Kuro\\Desktop\\Image.ppm", std::ios::out);

	if (ofs) {
		ofs << canvas.toPPM() << std::endl;
		ofs.close();
	}
}