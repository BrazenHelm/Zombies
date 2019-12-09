#include "SpriteBatch.h"

#include <algorithm>
#include <iostream>

namespace MyGameEngine {

Glyph::Glyph(const glm::vec4& rect, const glm::vec4& uv, GLuint texture, float depth, const Color& color) :
	texture(texture), depth(depth)
{
	v00.SetPosition(rect[0], rect[1]);
	v00.color = color;
	v00.SetUV(uv[0], uv[1]);

	v01.SetPosition(rect[0], rect[1] + rect[3]);
	v01.color = color;
	v01.SetUV(uv[0], uv[1] + uv[3]);

	v10.SetPosition(rect[0] + rect[2], rect[1]);
	v10.color = color;
	v10.SetUV(uv[0] + uv[2], uv[1]);

	v11.SetPosition(rect[0] + rect[2], rect[1] + rect[3]);
	v11.color = color;
	v11.SetUV(uv[0] + uv[2], uv[1] + uv[3]);
}


Glyph::Glyph(const glm::vec4& rect, const glm::vec4& uv, GLuint texture, float depth, const Color& color, float angle) : 
	texture(texture), depth(depth)
{
	glm::vec2 halfDimensions(rect[2] / 2, rect[3] / 2);

	glm::vec2 bl(-halfDimensions.x,  halfDimensions.y);
	glm::vec2 br( halfDimensions.x,  halfDimensions.y);
	glm::vec2 tl(-halfDimensions.x, -halfDimensions.y);
	glm::vec2 tr( halfDimensions.x, -halfDimensions.y);

	bl = rotatePoint(bl, angle) + halfDimensions;
	br = rotatePoint(br, angle) + halfDimensions;
	tl = rotatePoint(tl, angle) + halfDimensions;
	tr = rotatePoint(tr, angle) + halfDimensions;

	v00.SetPosition(rect[0] + bl.x, rect[1] + bl.y);
	v00.color = color;
	v00.SetUV(uv[0], uv[1]);

	v01.SetPosition(rect[0] + br.x, rect[1] + br.y);
	v01.color = color;
	v01.SetUV(uv[0], uv[1] + uv[3]);

	v10.SetPosition(rect[0] + tl.x, rect[1] + tl.y);
	v10.color = color;
	v10.SetUV(uv[0] + uv[2], uv[1]);

	v11.SetPosition(rect[0] + tr.x, rect[1] + tr.y);
	v11.color = color;
	v11.SetUV(uv[0] + uv[2], uv[1] + uv[3]);
}


glm::vec2 Glyph::rotatePoint(const glm::vec2& point, float angle) {
	glm::vec2 result(
		point.x * cos(angle) - point.y * sin(angle),
		point.x * sin(angle) + point.y * cos(angle)
	);
	return result;
}


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
	//for (Glyph* pGlyph : m_pGlyphs) {
	//	delete pGlyph;
	//}
	//m_pGlyphs.clear();
	m_glyphs.clear();
	m_renderBatches.clear();
}


void SpriteBatch::End() {
	m_pGlyphs.resize(m_glyphs.size());
	for (size_t i = 0; i < m_glyphs.size(); i++) { m_pGlyphs[i] = &m_glyphs[i]; }
	SortGlyphs();
	CreateRenderBatches();
}


void SpriteBatch::Draw(const glm::vec4& rect, const glm::vec4& uv, GLuint texture, float depth, const Color& color) {
	m_glyphs.emplace_back(rect, uv, texture, depth, color);
}


void SpriteBatch::Draw(const glm::vec4& rect, const glm::vec4& uv, GLuint texture, float depth, const Color& color, float angle) {
	m_glyphs.emplace_back(rect, uv, texture, depth, color, angle);
}


void SpriteBatch::Draw(const glm::vec4& rect, const glm::vec4& uv, GLuint texture, float depth, const Color& color, const glm::vec2& dir) {
	const glm::vec2 down(0.0f, -1.0f);
	float angle = acos(glm::dot(dir, down) / glm::length(dir));
	if (dir.x < 0) angle *= -1;
	m_glyphs.emplace_back(rect, uv, texture, depth, color, angle);
}


void SpriteBatch::Render() {
	glBindVertexArray(m_vaoID);
	for (size_t i = 0; i < m_renderBatches.size(); ++i) {
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

	glBindVertexArray(0);
}


void SpriteBatch::SortGlyphs() {
	switch (m_sortType) {
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(m_pGlyphs.begin(), m_pGlyphs.end(), CompareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_pGlyphs.begin(), m_pGlyphs.end(), CompareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(m_pGlyphs.begin(), m_pGlyphs.end(), CompareTexture);
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

	if (m_pGlyphs.empty()) return;

	const int VERTICES_PER_GLYPH = 4;

	std::vector<Vertex> vertices;
	vertices.resize(m_pGlyphs.size() * VERTICES_PER_GLYPH);

	int cv = 0; // current vertex

	m_renderBatches.emplace_back(cv, VERTICES_PER_GLYPH, m_pGlyphs[0]->texture);
	vertices[cv++] = m_pGlyphs[0]->v00;
	vertices[cv++] = m_pGlyphs[0]->v10;
	vertices[cv++] = m_pGlyphs[0]->v11;
	vertices[cv++] = m_pGlyphs[0]->v01;

	for (size_t glyph_itr = 1; glyph_itr < m_pGlyphs.size(); ++glyph_itr) {
		if (m_pGlyphs[glyph_itr]->texture != m_pGlyphs[glyph_itr - 1]->texture) {
			m_renderBatches.emplace_back(cv, VERTICES_PER_GLYPH, m_pGlyphs[glyph_itr]->texture);
		}
		else {
			m_renderBatches.back().IncrSize(VERTICES_PER_GLYPH);
		}
		vertices[cv++] = m_pGlyphs[glyph_itr]->v00;
		vertices[cv++] = m_pGlyphs[glyph_itr]->v10;
		vertices[cv++] = m_pGlyphs[glyph_itr]->v11;
		vertices[cv++] = m_pGlyphs[glyph_itr]->v01;
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