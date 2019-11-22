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


void SpriteBatch::Begin(GlyphSortType sortType /*= GlyphSortType::TEXTURE*/) {
	m_sortType = sortType;
	for (Glyph* glyph : m_glyphs) {
		delete glyph;
	}
	m_glyphs.clear();
	m_renderBatches.clear();
}


void SpriteBatch::End() {
	SortGlyphs();
	CreateRenderBatches();
}


void SpriteBatch::Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color) {
	
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
	glBindVertexArray(m_vaoID);
	for (int i = 0; i < m_renderBatches.size(); ++i) {
		glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].Texture());
		glDrawArrays(GL_QUADS, m_renderBatches[i].Offset(), m_renderBatches[i].Size());
	}
	glBindVertexArray(0);
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

	//glBindVertexArray(0);

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
		default:
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


void SpriteBatch::CreateRenderBatches() {

	if (m_glyphs.empty()) return;

	const int VERTICES_PER_GLYPH = 4;

	std::vector<Vertex> vertices;
	vertices.resize(m_glyphs.size() * VERTICES_PER_GLYPH);

	int cv = 0; // current vertex

	m_renderBatches.emplace_back(cv, VERTICES_PER_GLYPH, m_glyphs[0]->texture);
	vertices[cv++] = m_glyphs[0]->v00;
	vertices[cv++] = m_glyphs[0]->v10;
	vertices[cv++] = m_glyphs[0]->v11;
	vertices[cv++] = m_glyphs[0]->v01;

	for (int glyph_itr = 1; glyph_itr < m_glyphs.size(); ++glyph_itr) {
		if (m_glyphs[glyph_itr]->texture != m_glyphs[glyph_itr - 1]->texture) {
			m_renderBatches.emplace_back(cv, 1, m_glyphs[0]->texture);
		}
		else {
			m_renderBatches.back().IncrSize(VERTICES_PER_GLYPH);
		}
		vertices[cv++] = m_glyphs[glyph_itr]->v00;
		vertices[cv++] = m_glyphs[glyph_itr]->v10;
		vertices[cv++] = m_glyphs[glyph_itr]->v11;
		vertices[cv++] = m_glyphs[glyph_itr]->v01;
	}

	// bind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	// orphan the buffer
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	// upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	// unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}