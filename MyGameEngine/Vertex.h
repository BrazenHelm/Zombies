#pragma once

#include <GL/glew.h>

namespace MyGameEngine {

struct Vertex {

	struct Position {
		float x, y;
	} position;

	struct Color {
		GLubyte r, g, b, a;
	} color;

	// UV texture co-ordinates
	struct UV {
		float u, v;
	} uv;

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
