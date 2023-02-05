// NyxTracer.cpp : Defines the entry point for the application.
//

#include <iostream>

#include "graphics/Canvas.hpp"
#include "graphics/Color.hpp"
#include "graphics/Matrix.hpp"

int main()
{
	std::cout << Matrix::Identity() << std::endl;
	std::cout << Matrix::Identity().inverse() << std::endl;

	Matrix m1{
		MatrixRow4D(6, 4, 4, 4),
		MatrixRow4D(5, 5, 7, 6),
		MatrixRow4D(4, -9, 3, -7),
		MatrixRow4D(9, 1, 7, -6)
	};
	std::cout << m1 << std::endl;
	std::cout << m1.inverse() << std::endl;
	std::cout << m1 * m1.inverse() << std::endl;
	
	Matrix m2{
		MatrixRow4D(-5, 2, 6, -8),
		MatrixRow4D(1, -5, 1, 8),
		MatrixRow4D(7, 7, -6, -7),
		MatrixRow4D(1, -3, 7, 4)
	};
	std::cout << m2 << std::endl;
	std::cout << m2.transpose().inverse() << std::endl;
	std::cout << m2.inverse().transpose() << std::endl;

	Vector v1{ 1, 2, 3, 1 };
	std::cout << v1 << std::endl;
	std::cout << Matrix::Identity() * v1 << std::endl;
	Matrix m3 = Matrix::Identity();
	m3(0, 0) = 2;
	m3(1, 1) = 2.5;
	std::cout << m3 * v1 << std::endl;
}