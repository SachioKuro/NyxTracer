#pragma once

#include <exception>
#include <iostream>

#include "Vector.hpp"
#include "Point.hpp"


struct MatrixRow4D {
	MatrixRow4D(float x0, float x1, float x2, float x3)
		: x0(x0), x1(x1), x2(x2), x3(x3) {}

	float x0, x1, x2, x3;
};


class Matrix {
public:
	Matrix(int rows, int cols) : _rows(rows), _cols(cols), _data(new float[rows * cols]{0.f}) { }

	Matrix(MatrixRow4D r0, MatrixRow4D r1, MatrixRow4D r2, MatrixRow4D r3)
		: _rows(4), _cols(4),  _data(new float[16]()) {
		_data[ 0] = r0.x0;
		_data[ 1] = r0.x1;
		_data[ 2] = r0.x2;
		_data[ 3] = r0.x3;
		_data[ 4] = r1.x0;
		_data[ 5] = r1.x1;
		_data[ 6] = r1.x2;
		_data[ 7] = r1.x3;
		_data[ 8] = r2.x0;
		_data[ 9] = r2.x1;
		_data[10] = r2.x2;
		_data[11] = r2.x3;
		_data[12] = r3.x0;
		_data[13] = r3.x1;
		_data[14] = r3.x2;
		_data[15] = r3.x3;
	}
	
	Matrix(const Matrix& other) : _rows(other._rows), _cols(other._cols), _data(new float[_rows * _cols]) {
		for (int i = 0; i < _rows * _cols; i++) {
			_data[i] = other._data[i];
		}
	}
	
	Matrix(Matrix&& other) noexcept : _rows(other._rows), _cols(other._cols), _data(other._data) {
		other._data = nullptr;
	}
	
	Matrix& operator=(const Matrix& other) {
		if (this != &other) {
			delete[] _data;
			_rows = other._rows;
			_cols = other._cols;
			_data = new float[_rows * _cols];
			for (int i = 0; i < _rows * _cols; i++) {
				_data[i] = other._data[i];
			}
		}
		return *this; 
	}
	
	Matrix& operator=(Matrix&& other) noexcept {
		if (this != &other) {
			delete[] _data;
			_rows = other._rows;
			_cols = other._cols;
			_data = other._data;
			other._data = nullptr;
		}
		return *this;
	}
	
	virtual ~Matrix() { 
		delete[] _data;
	}

	float operator()(int row, int col) const { return _data[row * _cols + col]; }
	float& operator()(int row, int col) { return _data[row * _cols + col]; }

	int rows() const { return _rows; }
	int cols() const { return _cols; }
	
	bool operator==(const Matrix& other) const {
		if (_rows != other._rows || _cols != other._cols)
			return false;
		for (int i = 0; i < _rows * _cols; i++) {
			if (abs(_data[i] - other._data[i]) >= EPSILON)
				return false;
		}
		return true;
	}

	bool operator!=(const Matrix& other) const {
		return !(*this == other);
	}

	Matrix operator*(const Matrix& other) const {
		Matrix result(_rows, other._cols);
		for (int i = 0; i < _rows; i++) {
			for (int j = 0; j < other._cols; j++) {
				for (int k = 0; k < _cols; k++) {  
					result(i, j) += (*this)(i, k) * other(k, j);
				}
			}
		}
		return result;
	}
	
	Vector operator*(const Vector& v) const {
		if (_cols != 4)
			throw std::exception("Matrix must be 4x4");
		return Vector(
			_data[0] * v.x + _data[1] * v.y + _data[2] * v.z + _data[3] * v.w,
			_data[4] * v.x + _data[5] * v.y + _data[6] * v.z + _data[7] * v.w,
			_data[8] * v.x + _data[9] * v.y + _data[10] * v.z + _data[11] * v.w,
			_data[12] * v.x + _data[13] * v.y + _data[14] * v.z + _data[15] * v.w
		);
	}

	Point operator*(const Point& p) const {
		if (_cols != 4)
			throw std::exception("Matrix must be 4x4");
		return Point(
			_data[0] * p.x + _data[1] * p.y + _data[2] * p.z + _data[3] * p.w,
			_data[4] * p.x + _data[5] * p.y + _data[6] * p.z + _data[7] * p.w,
			_data[8] * p.x + _data[9] * p.y + _data[10] * p.z + _data[11] * p.w,
			_data[12] * p.x + _data[13] * p.y + _data[14] * p.z + _data[15] * p.w
		);
	}

	static Matrix Identity(int rows = 4) {
		return Matrix(
			MatrixRow4D(1, 0, 0, 0),
			MatrixRow4D(0, 1, 0, 0),
			MatrixRow4D(0, 0, 1, 0),
			MatrixRow4D(0, 0, 0, 1)
		);
	}

	Matrix transpose() {
		Matrix m = *this;
		for (int i = 0; i < _rows; ++i)
			for (int j = 0; j < _cols; ++j)
				m(i, j) = (*this)(j, i);
		return m;
	}

	float determinant() {
		if (_rows == 2 && _cols == 2) {
			return _data[0] * _data[3] - _data[1] * _data[2];
		}
		else {
			float det = 0;
			for (int i = 0; i < _cols; ++i) {
				det += _data[i] * this->cofactor(0, i);
			}
			return det;
		}
	}

	Matrix submatrix(int row, int col) {
		Matrix out(_rows - 1, _cols - 1);
		int i_sub = 0;
		for (int i = 0; i < _rows; ++i) {
			if (i == row) continue;
			int j_sub = 0;
			for (int j = 0; j < _cols; ++j) {
				if (j == col) continue;

				out(i_sub, j_sub) = (*this)(i, j);
				++j_sub;
			}
			++i_sub;
		}
		return out;
	}

	float minor(int row, int col) {
		return this->submatrix(row, col).determinant();
	}

	float cofactor(int row, int col) {
		// + - + - +
		// - + - + -
		// + - + - +
		// - + - + -
		// + - + - +
		return this->minor(row, col) * (1 - ((row + col) % 2) * 2);
	}

	bool isInvertable() {
		return this->determinant() != 0;
	}

	Matrix inverse() {
		if (!this->isInvertable())
			throw std::exception("Matrix is not invertable");

		Matrix out(_rows, _cols);

		float det = this->determinant();
		for (int i = 0; i < _rows; ++i) {
			for (int j = 0; j < _rows; ++j) {
				out(j, i) = this->cofactor(i, j) / det;
			}
		}

		return out;
	}

protected:
	int _rows, _cols;
	float* _data;
};

std::ostream& operator<<(std::ostream&, const Matrix&);