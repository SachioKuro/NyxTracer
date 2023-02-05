#pragma once

#include <sstream>
#include <format>

#include "Color.hpp"

class Canvas {
public:
	Canvas(uint16_t width, uint16_t height)
		: _width(width), _height(height), _pixels(new Color[width * height] {Color(0, 0, 0)}) { }
	virtual ~Canvas() { delete[] _pixels; }

	uint16_t width() const { return _width; }
	uint16_t height() const { return _height; }

	Color operator()(uint16_t x, uint16_t y) const { return _pixels[y * _width + x]; }
	Color& operator()(uint16_t x, uint16_t y) { return _pixels[y * _width + x]; }

	std::string toPPM() const {
		std::stringstream ss;
		ss << "P3\n" << _width << " " << _height << "\n255\n";
		for (int i = 0; i < _height; i++) {
			for (int j = 0; j < _width; j++) {
				Color c = _pixels[i * _width + j];
				ss << std::format("{} {} {}", int(c.r * 255), int(c.g * 255), int(c.b * 255));
				if (j % 5 == 4) {
					ss << "\n";
				}
				else if (j < _width - 1) {
					ss << " ";
				}
			}
			if (_width % 5 != 0)
				ss << "\n";
		}
		return ss.str();
	}
private:
	uint16_t _width, _height;

	Color* _pixels;
};