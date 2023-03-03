#pragma once

#include "Color.hpp"
#include "Light.hpp"

struct BasicMaterial {
	BasicMaterial(Color color, float ambient, float diffuse, float specular, float shininess)
		: color(color), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

	Color color;
	float ambient;
	float diffuse;
	float specular;
	float shininess;

	bool operator==(const BasicMaterial& other) const {
		return color == other.color &&
			abs(ambient - other.ambient) < EPSILON &&
			abs(diffuse - other.diffuse) < EPSILON &&
			abs(specular - other.specular) < EPSILON &&
			abs(shininess - other.shininess) < EPSILON;
	}

	bool operator!=(const BasicMaterial& other) const {
		return !(*this == other);
	}

	Color lighting(PointLight pl, Point pos, Vector eye, Vector normal) const {
		Color effectiveCol = color * pl.intensity;
		Color ambientCol = effectiveCol * ambient;
		Color diffuseCol = Color(0, 0, 0);
		Color specularCol = Color(0, 0, 0);
		
		Vector lightVec = (pl.position - pos).normalize();
		float lightDotNormal = lightVec.dot(normal);

		if (lightDotNormal >= 0) {
			diffuseCol = effectiveCol * diffuse * lightDotNormal;
			Vector reflectVec = (-lightVec).reflect(normal);
			float reflectDotEye = reflectVec.dot(eye);

			if (reflectDotEye > 0) {
				float specularFactor = pow(reflectDotEye, shininess);
				specularCol = pl.intensity * specular * specularFactor;
			}
		}
		return ambientCol + diffuseCol + specularCol;
	}
};