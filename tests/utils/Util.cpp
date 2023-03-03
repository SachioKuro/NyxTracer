#include "Util.hpp"

#include <stdlib.h>
#include <cmath>
#include <format>



bool isClose(float a, float b, float epsilon) {
	return abs(a - b) < epsilon;
}

bool isClose(Point a, Point b, float epsilon) {
	return isClose(a.x, b.x, epsilon) && isClose(a.y, b.y, epsilon) && isClose(a.z, b.z, epsilon);
}

bool isClose(Vector a, Vector b, float epsilon) {
	return isClose(a.x, b.x, epsilon) && isClose(a.y, b.y, epsilon) && isClose(a.z, b.z, epsilon);
}

bool isClose(Matrix a, Matrix b, float epsilon) {
	if (a.rows() != b.rows() || a.cols() != b.cols())
		return false;
	for (int i = 0; i < a.rows(); ++i)
		for (int j = 0; j < a.cols(); ++j)
			if (!isClose(a(i, j), b(i, j), epsilon))
				return false;
	return true;
}

float randomFloat(float min, float max) {
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

float randomInt(int min, int max) {
	return min + rand() % (max - min);
}

Point randomPoint(float minValue, float maxValue) {
	return Point(randomFloat(minValue, maxValue), randomFloat(minValue, maxValue), randomFloat(minValue, maxValue));
}
	
Vector randomVector(float minValue, float maxValue) {
	return Vector(randomFloat(minValue, maxValue), randomFloat(minValue, maxValue), randomFloat(minValue, maxValue));
}

MatrixRow4D randomMatrixRow4D(float minValue, float maxValue) {
	return MatrixRow4D(
		randomFloat(minValue, maxValue),
		randomFloat(minValue, maxValue),
		randomFloat(minValue, maxValue),
		randomFloat(minValue, maxValue)
	);
}

Matrix randomMatrix4x4(float minValue, float maxValue) {
	return Matrix(
		randomMatrixRow4D(minValue, maxValue),
		randomMatrixRow4D(minValue, maxValue),
		randomMatrixRow4D(minValue, maxValue),
		randomMatrixRow4D(minValue, maxValue)
	);
}