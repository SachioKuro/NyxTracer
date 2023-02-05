#include "Matrix.hpp"
#include <iomanip>

bool print_isClose(float a, float b, float epsilon = 0.001) {
	return abs(a - b) < epsilon;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
	os << "Matrix(" << m.rows() << ", " << m.cols() << ")\n";
	for (int i = 0; i < m.rows(); ++i) {
		os << "\t";
		for (int j = 0; j < m.cols(); ++j) {
			float current = m(i, j);
			os << std::fixed << std::setprecision(2) << (print_isClose(current, 0.f) ? abs(current) : current) << " ";
		}
		os << "\n";
	}
	return os;
}