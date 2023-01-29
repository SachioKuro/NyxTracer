#pragma once

struct Vector {
	Vector(float x, float y, float z) : x(x), y(y), z(z) { }

	float x;
	float y;
	float z;
	float w = 0.0f;

	bool operator==(const Vector& other) const {
		return x == other.x && y == other.y && z == other.z;
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
};