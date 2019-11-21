#include "SpriteBatch.h"

#include <algorithm>

namespace MyGameEngine {

SpriteBatch::SpriteBatch() :
	m_vboID(0), m_vaoID(0) {
}


SpriteBatch::~SpriteBatch() {
}


void SpriteBatch::Init() {
	CreateVertexArray();
}


void SpriteBatch::Begin(GlyphSortType sortType = GlyphSortType::TEXTURE) {
	m_sortType = sortType;
}


void SpriteBatch::End() {
	SortGlyphs();
}


void SpriteBatch::Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color) {
	/*
	m_glyphs.emplace_back(
		texture, depth,
		destRect[0], destRect[1], color, uvRect[0], uvRect[1],
		destRect[0] + destRect[2], destRect[1], color, uvRect[0] + uvRect[2], uvRect[1],
		destRect[0] + destRect[2], destRect[1] + destRect[3], color, uvRect[0] + uvRect[2], uvRect[1] + uvRect[3],
		destRect[0], destRect[1] + destRect[3], color, uvRect[0], uvRect[1] + uvRect[3]
	);
	*/
	Glyph* newGlyph = new Glyph;

	newGlyph->texture = texture;
	newGlyph->depth = depth;

	newGlyph->v00.SetPosition(destRect[0], destRect[1]);
	newGlyph->v00.color = color;
	newGlyph->v00.SetUV(uvRect[0], uvRect[1]);

	newGlyph->v01.SetPosition(destRect[0], destRect[1] + destRect[3]);
	newGlyph->v01.color = color;
	newGlyph->v01.SetUV(uvRect[0], uvRect[1] + uvRect[3]);

	newGlyph->v10.SetPosition(destRect[0] + destRect[2], destRect[1]);
	newGlyph->v10.color = color;
	newGlyph->v10.SetUV(uvRect[0] + uvRect[2], uvRect[1]);

	newGlyph->v11.SetPosition(destRect[0] + destRect[2], destRect[1] + destRect[3]);
	newGlyph->v11.color = color;
	newGlyph->v11.SetUV(uvRect[0] + uvRect[2], uvRect[1] + uvRect[3]);

	m_glyphs.push_back(newGlyph);
}


void SpriteBatch::Render() {

}


void SpriteBatch::CreateVertexArray() {

	if (m_vaoID == 0) {
		glGenVertexArrays(1, &m_vaoID);
	}
	glBindVertexArray(m_vaoID);

	if (m_vboID == 0) {
		glGenBuffers(1, &m_vboID);
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);

}


void SpriteBatch::SortGlyphs() {
	switch (m_sortType) {
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(m_glyphs.begin(), m_glyphs.end(), CompareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_glyphs.begin(), m_glyphs.end(), CompareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(m_glyphs.begin(), m_glyphs.end(), CompareTexture);
			break;
	}

}


bool SpriteBatch::CompareBackToFront(Glyph* a, Glyph* b) {
	return (a->depth > b->depth);
}


bool SpriteBatch::CompareFrontToBack(Glyph* a, Glyph* b) {
	return (a->depth < b->depth);
}


bool SpriteBatch::CompareTexture(Glyph* a, Glyph* b) {
	return (a->texture < b->texture);
}

}