#pragma once

#include <array>
#include <cmath>

#include "common/UUID.hpp"
#include "Intersections.hpp"
#include "Matrix.hpp"
#include "Material.hpp"
#include "Point.hpp"
#include "Ray.hpp"

struct Sphere {
	Sphere(Matrix transformation = Matrix::Identity(), BasicMaterial material = BasicMaterial(Color(1, 1, 1), .1, .9, .9, 200))
		: transform(transformation), material(material) {}

	Matrix transform;
	BasicMaterial material;

	uuid64 getUUID() {
		return id;
	}

	Intersections intersect(Ray ray) const {
		ray = ray * transform.inverse();
		Vector sphereToOrigin = ray.origin - Point(0, 0, 0);
		float det = pow(2 * ray.direction.dot(sphereToOrigin), 2) - 4 * ray.direction.dot(ray.direction) *
			(sphereToOrigin.dot(sphereToOrigin) - 1);
		if (det < 0)
			return Intersections();
		float t1 = (-2 * ray.direction.dot(sphereToOrigin) - sqrt(det)) / (2 * ray.direction.dot(ray.direction));
		float t2 = (-2 * ray.direction.dot(sphereToOrigin) + sqrt(det)) / (2 * ray.direction.dot(ray.direction));

		if (t1 < t2) return Intersections({ Intersection(t1, id), Intersection(t2, id) });
		else         return Intersections({ Intersection(t2, id), Intersection(t1, id) });
	}

	Vector normalAt(Point wp) {
		Matrix inverse = transform.inverse();
		Point op = inverse * wp;
		Vector on = op - Point(0, 0, 0);
		Vector wn = inverse.transpose() * on;
		wn.w = 0;
		return wn.normalize();
	}
private:
	uuid64 id = GenerateUUID();
};