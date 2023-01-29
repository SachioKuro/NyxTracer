#include "Util.hpp"

#include <cmath>

bool isClose(float a, float b, float epsilon) {
	return abs(a - b) < epsilon;
}

float randomFloat(float min, float max) {
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}