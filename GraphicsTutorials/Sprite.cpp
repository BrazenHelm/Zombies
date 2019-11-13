#include "Sprite.h"



Sprite::Sprite() :
	m_vboID(0) {
}


Sprite::~Sprite() {
	if (m_vboID != 0) {
		glDeleteBuffers(1, &m_vboID);
	}
}


void Sprite::Init(float x, float y, float width, float height) {
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;

	if (m_vboID == 0) {
		glGenBuffers(1, &m_vboID);
	}

	float vertexData[8];
	vertexData[0] = x;
	vertexData[1] = y;
	vertexData[2] = x + width;
	vertexData[3] = y;
	vertexData[4] = x + width;
	vertexData[5] = y + height;
	vertexData[6] = x;
	vertexData[7] = y + height;

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Sprite::Draw() {
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_QUADS, 0, 4);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}