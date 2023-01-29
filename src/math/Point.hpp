#pragma once

struct Point {
	Point(float x, float y, float z) : x(x), y(y), z(z) { }
	
	float x;
	float y;
	float z;
	float w = 1.0f;
};