#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "Matrix.hpp"

class Transformation {
public:
	static Matrix Translation(float x, float y, float z) {
		return Matrix(
			MatrixRow4D(1, 0, 0, x),
			MatrixRow4D(0, 1, 0, y),
			MatrixRow4D(0, 0, 1, z),
			MatrixRow4D(0, 0, 0, 1)
		);
	}

	static Matrix Scaling(float x, float y, float z) {
		return Matrix(
			MatrixRow4D(x, 0, 0, 0),
			MatrixRow4D(0, y, 0, 0),
			MatrixRow4D(0, 0, z, 0),
			MatrixRow4D(0, 0, 0, 1)
		);
	}

	static Matrix RotationX(float rad) {
		return Matrix(
			MatrixRow4D(1, 0, 0, 0),
			MatrixRow4D(0, cos(rad), -sin(rad), 0),
			MatrixRow4D(0, sin(rad), cos(rad), 0),
			MatrixRow4D(0, 0, 0, 1)
		);
	}

	static Matrix RotationY(float rad) {
		return Matrix(
			MatrixRow4D(cos(rad), 0, sin(rad), 0),
			MatrixRow4D(0, 1, 0, 0),
			MatrixRow4D(-sin(rad), 0, cos(rad), 0),
			MatrixRow4D(0, 0, 0, 1)
		);
	}

	static Matrix RotationZ(float rad) {
		return Matrix(
			MatrixRow4D(cos(rad), -sin(rad), 0, 0),
			MatrixRow4D(sin(rad), cos(rad), 0, 0),
			MatrixRow4D(0, 0, 1, 0),
			MatrixRow4D(0, 0, 0, 1)
		);
	}
};