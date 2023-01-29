#include "Util.hpp"

#include <stdlib.h>
#include <cmath>
#include <format>


bool isClose(float a, float b, float epsilon) {
	return abs(a - b) < epsilon;
}

float randomFloat(float min, float max) {
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

Point randomPoint(float minValue, float maxValue) {
	return Point(randomFloat(minValue, maxValue), randomFloat(minValue, maxValue), randomFloat(minValue, maxValue));
}
	
Vector randomVector(float minValue, float maxValue) {
	return Vector(randomFloat(minValue, maxValue), randomFloat(minValue, maxValue), randomFloat(minValue, maxValue));
}