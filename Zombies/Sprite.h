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
	void Draw(MyGameEngine::SpriteBatch& spriteBatch, glm::vec2 position, glm::vec2 size, glm::vec2 dir);

private:
	GLuint					m_textureID;
	MyGameEngine::Color		m_color;

	bool m_isInit;
};

