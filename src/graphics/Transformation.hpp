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

	static Matrix Shearing(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y) {
		return Matrix(
			MatrixRow4D(1, x_y, x_z, 0),
			MatrixRow4D(y_x, 1, y_z, 0),
			MatrixRow4D(z_x, z_y, 1, 0),
			MatrixRow4D(0, 0, 0, 1)
		);
	}

	Transformation identity() {
		tmp = Matrix::Identity(4);
		return *this;
	}

	Transformation translate(float x, float y, float z) {
		tmp = Translation(x, y, z) * tmp;
		return *this;
	}

	Transformation scale(float x, float y, float z) {
		tmp = Scaling(x, y, z) * tmp;
		return *this;
	}

	Transformation rotateX(float rad) {
		tmp = RotationX(rad) * tmp;
		return *this;
	}

	Transformation rotateY(float rad) {
		tmp = RotationY(rad) * tmp;
		return *this;
	}

	Transformation rotateZ(float rad) {
		tmp = RotationZ(rad) * tmp;
		return *this;
	}

	Transformation shear(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y) {
		tmp = Shearing(x_y, x_z, y_x, y_z, z_x, z_y) * tmp;
		return *this;
	}

	Matrix toMatrix() const {
		return tmp;
	}

private:
	Matrix tmp = Matrix::Identity();
};