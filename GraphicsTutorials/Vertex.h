#pragma once

#include <cstdint>

struct Vertex {

	struct Position {
		float x;
		float y;
	} position;

	struct Color {
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	} color;
};
