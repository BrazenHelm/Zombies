#include "Sprite.h"

#include <iostream>

#include <MyGameEngine/Vertex.h>
#include <MyGameEngine/ResourceManager.h>


Sprite::Sprite() :
	m_isInit(false) {
}


Sprite::~Sprite() {
}


void Sprite::Draw(MyGameEngine::SpriteBatch& spriteBatch, glm::vec2 position, glm::vec2 dimensions) {

	if (!m_isInit) {
		std::cout << "Tried to draw uninitialised sprite." << std::endl;
		return;
	}

	glm::vec4 rect = glm::vec4(
		position.x - dimensions.x / 2.0f,
		position.y - dimensions.y / 2.0f,
		dimensions.x,
		dimensions.y
	);
	glm::vec4 uv = glm::vec4(0, 0, 1, 1);

	spriteBatch.Draw(rect, uv, m_textureID, 0, m_color);
}


void Sprite::Draw(MyGameEngine::SpriteBatch& spriteBatch, glm::vec2 position, glm::vec2 dimensions, glm::vec2 direction) {

	if (!m_isInit) {
		std::cout << "Tried to draw uninitialised sprite." << std::endl;
		return;
	}

	glm::vec4 rect = glm::vec4(
		position.x - dimensions.x / 2.0f,
		position.y - dimensions.y / 2.0f,
		dimensions.x,
		dimensions.y
	);
	glm::vec4 uv = glm::vec4(0, 0, 1, 1);

	spriteBatch.Draw(rect, uv, m_textureID, 0, m_color, direction);
}


void Sprite::Init(const std::string& path, const MyGameEngine::Color& color) {
	m_textureID = MyGameEngine::ResourceManager::GetTexture(path).id;
	m_color = color;
	m_isInit = true;
}
