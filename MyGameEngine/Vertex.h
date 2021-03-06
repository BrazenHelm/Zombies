#pragma once

#include <GL/glew.h>

namespace MyGameEngine {

struct Position {
	float x, y;
};

struct Color {
	GLubyte r, g, b, a;

	Color() : r(0), g(0), b(0), a(255) { }
	Color(GLubyte r, GLubyte g, GLubyte b, GLubyte a) :
		r(r), g(g), b(b), a(a) {
	}
};

struct UV {
	float u, v;
};

struct Vertex {

	Position position;
	Color color;
	UV uv;

	void SetPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}

	void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void SetUV(float u, float v) {
		uv.u = u;
		uv.v = v;
	}
};

}
