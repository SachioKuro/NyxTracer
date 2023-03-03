#pragma once

#include <vector>
#include <cmath>
#include <optional>

#include "common/UUID.hpp"
#include "Point.hpp"

struct Intersection {
	Intersection(float t, uuid64 obj) : t(t), obj(obj) {}

	bool operator==(const Intersection& other) const {
		return t == other.t && obj == other.obj;
	}

	bool operator!=(const Intersection& other) const {
		return !(*this == other);
	}

	float t;
	uuid64 obj;
};

struct Intersections {
	Intersections() = default;
	Intersections(std::vector<Intersection> data) : data(data) {}

	bool operator==(const Intersections& other) const {
		if (data.size() != other.data.size()) 
			return false;
		for (auto i = 0; i < data.size(); ++i)
			if (abs(data[i].t - other.data[i].t) > EPSILON)
				return false;
		return true;
	}

	bool operator!=(const Intersections& other) const {
		return !(*this == other);
	}

	std::optional<Intersection> hit() const {
		for (auto& intersection : data)
			if (intersection.t > 0)
				return intersection;
		return std::nullopt;
	}

	std::vector<Intersection> data;
};
