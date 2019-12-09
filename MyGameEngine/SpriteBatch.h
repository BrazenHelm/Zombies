#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"

namespace MyGameEngine {

enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};


class Glyph
{
public:
	GLuint texture;
	float depth;

	Vertex v00;
	Vertex v01;
	Vertex v10;
	Vertex v11;

	Glyph() { }
	Glyph(const glm::vec4& rect, const glm::vec4& uv, GLuint texture, float depth, const Color& color);
	Glyph(const glm::vec4& rect, const glm::vec4& uv, GLuint texture, float depth, const Color& color, float angle);

private:
	glm::vec2 rotatePoint(const glm::vec2& point, float angle);
};


class RenderBatch
{
private:
	GLuint m_offset;
	GLuint m_size;
	GLuint m_texture;

public:
	RenderBatch(GLuint offset, GLuint size, GLuint texture) :
		m_offset(offset), m_size(size), m_texture(texture) {
	}

	void IncrSize(GLuint value) { m_size += value; }

	GLuint Offset()		{ return m_offset; }
	GLuint Size()		{ return m_size; }
	GLuint Texture()	{ return m_texture; }
};


class SpriteBatch
{
private:
	GLuint m_vboID;
	GLuint m_vaoID;

	std::vector<Glyph*> m_pGlyphs;	//< used only for sorting
	std::vector<Glyph> m_glyphs;
	GlyphSortType m_sortType;

	std::vector<RenderBatch> m_renderBatches;

public:
	SpriteBatch();
	~SpriteBatch();

	void Init();
	void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void End();
	void Draw(const glm::vec4& rect, const glm::vec4& uv, GLuint texture, float depth, const Color& color);
	void Draw(const glm::vec4& rect, const glm::vec4& uv, GLuint texture, float depth, const Color& color, float angle);
	void Draw(const glm::vec4& rect, const glm::vec4& uv, GLuint texture, float depth, const Color& color, const glm::vec2& dir);
	void Render();

private:
	void CreateVertexArray();
	void SortGlyphs();

	static bool CompareBackToFront	(Glyph* a, Glyph* b);
	static bool CompareFrontToBack	(Glyph* a, Glyph* b);
	static bool CompareTexture		(Glyph* a, Glyph* b);

	void CreateRenderBatches();
};

}
