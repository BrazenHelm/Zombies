#include "Sprite.h"
#include "Vertex.h"


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

	Vertex vertexData[4];
	vertexData[0].position.x = x;
	vertexData[0].position.y = y;
	vertexData[1].position.x = x + width;
	vertexData[1].position.y = y;
	vertexData[2].position.x = x + width;
	vertexData[2].position.y = y + height;
	vertexData[3].position.x = x;
	vertexData[3].position.y = y + height;

	for (int i = 0; i < 4; ++i) {
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 20;
		vertexData[i].color.b = 143;
		vertexData[i].color.a = 255;
	}

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