#pragma once

struct Vector {
	Vector(float x, float y, float z) : x(x), y(y), z(z) { }

	float x;
	float y;
	float z;
	float w = 0.0f;
};