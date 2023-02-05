#pragma once

struct Tuple4D {

	Tuple4D() = default;
	Tuple4D(float t1, float t2, float t3, float t4) : t1(t1), t2(t2), t3(t3), t4(t4) { }

	float t1;
	float t2;
	float t3;
	float t4;
	
	bool operator==(const Tuple4D& other) const {
		return abs(t1 - other.t1) < EPSILON && abs(t2 - other.t2) < EPSILON && abs(t3 - other.t3) < EPSILON;
	}

	bool operator!=(const Tuple4D& other) const {
		return !(*this == other);
	}
	
};