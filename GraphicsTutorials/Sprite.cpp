#include "Sprite.h"
#include "Vertex.h"

#include <cstddef>

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

	vertexData[0].SetPosition(x, y);
	vertexData[1].SetPosition(x + width, y);
	vertexData[2].SetPosition(x + width, y + height);
	vertexData[3].SetPosition(x, y + height);

	vertexData[0].SetColor(255, 255, 255, 255);
	vertexData[1].SetColor(255, 20, 143, 255);
	vertexData[2].SetColor(255, 255, 255, 255);
	vertexData[3].SetColor(255, 20, 143, 255);

	vertexData[0].SetUV(0, 0);
	vertexData[1].SetUV(1, 0);
	vertexData[2].SetUV(1, 1);
	vertexData[3].SetUV(0, 1);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Sprite::Draw() {
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glDrawArrays(GL_QUADS, 0, 4);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

