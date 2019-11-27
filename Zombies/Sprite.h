#pragma once

#include <string>

#include <MyGameEngine/GLTexture.h>
#include <MyGameEngine/SpriteBatch.h>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Init(const std::string& path, const MyGameEngine::Color& color);

	void Draw(MyGameEngine::SpriteBatch& spriteBatch, glm::vec2 position, glm::vec2 size);

private:
	MyGameEngine::GLTexture		m_texture;
	MyGameEngine::Color			m_color;

	bool m_isInit;
};

