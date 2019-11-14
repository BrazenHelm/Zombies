#pragma once

#include "GLTexture.h"

#include <GL/glew.h>
#include <string>

class Sprite {
private:
	float m_x;
	float m_y;
	float m_width;
	float m_height;
	GLTexture m_texture;

	GLuint m_vboID;

public:
	Sprite();
	~Sprite();

	void Init(float x, float y, float width, float height, const std::string& texturePath);
	void Draw();
};

