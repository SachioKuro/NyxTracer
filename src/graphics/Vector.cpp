#include "Vector.hpp"
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const Vector& v) {
	os << "Vector(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")\n";
	return os;
}