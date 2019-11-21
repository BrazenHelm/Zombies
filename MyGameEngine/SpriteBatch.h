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

struct Glyph {
	GLuint texture;
	float depth;

	Vertex v00;
	Vertex v01;
	Vertex v10;
	Vertex v11;
};

class RenderBatch
{

};

class SpriteBatch
{
private:
	void CreateVertexArray();
	void SortGlyphs();

	GLuint m_vboID;
	GLuint m_vaoID;

	std::vector<Glyph*> m_glyphs;
	GlyphSortType m_sortType;

	static bool CompareBackToFront(Glyph* a, Glyph* b);
	static bool CompareFrontToBack(Glyph* a, Glyph* b);
	static bool CompareTexture(Glyph* a, Glyph* b);

public:
	SpriteBatch();
	~SpriteBatch();

	void Init();
	void Begin(GlyphSortType sortType /*= GlyphSortType::TEXTURE*/);
	void End();
	void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);
	void Render();
};

}
