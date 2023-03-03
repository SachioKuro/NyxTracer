#pragma once

#include <cmath>
#include <iostream>

#include "Constants.hpp"


struct Vector {

	Vector() = default;
	Vector(float x, float y, float z) : x(x), y(y), z(z), w(0) { }
	Vector(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }

	float x, y, z, w;

	bool operator==(const Vector& other) const {
		return abs(x - other.x) < EPSILON && abs(y - other.y) < EPSILON && abs(z - other.z) < EPSILON;
	}

	bool operator!=(const Vector& other) const {
		return !(*this == other);
	}

	Vector operator+(const Vector& other) const {
		return Vector(x + other.x, y + other.y, z + other.z);
	}

	Vector operator-(const Vector& other) const {
		return Vector(x - other.x, y - other.y, z - other.z);
	}

	Vector operator-() const {
		return Vector(-x, -y, -z);
	}
	
	Vector operator*(float scalar) const {
		return Vector(x * scalar, y * scalar, z * scalar);
	}
	
	Vector operator/(float scalar) const {
		return Vector(x / scalar, y / scalar, z / scalar);
	}

	float length() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	Vector normalize() const {
		float length = this->length();
		
		if (length == 0) {
			return Vector(0, 0, 0);
		}

		return *this / length;
	}
	
	float dot(const Vector& other) const {
		return x * other.x + y * other.y + z * other.z;
	}

	Vector cross(const Vector& other) const {
		return Vector(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	Vector reflect(const Vector& normal) const {
		return (*this) - (normal * 2 * this->dot(normal));
	}
};

std::ostream& operator<<(std::ostream&, const Vector&);