#pragma once

#include <string>

#include <MyGameEngine/GLTexture.h>
#include <MyGameEngine/SpriteBatch.h>

class Sprite
{
public:
	Sprite(const glm::vec2& position, const glm::vec2& dimensions);
	~Sprite();

	void Init(const std::string& path, const MyGameEngine::Color& color);

	void Draw(MyGameEngine::SpriteBatch& spriteBatch);

private:
	MyGameEngine::GLTexture		m_texture;
	MyGameEngine::Color			m_color;
	glm::vec4					m_rectTransform;

	bool m_isInit;

};

