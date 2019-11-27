#include "Sprite.h"

#include <iostream>

#include <MyGameEngine/Vertex.h>
#include <MyGameEngine/ResourceManager.h>

#include "Transform.h"



Sprite::Sprite(const glm::vec2& position, const glm::vec2& dimensions) :
	m_rectTransform(position.x, position.y, dimensions.x, dimensions.y),
	m_isInit(false) {
}


Sprite::~Sprite() {
}


void Sprite::Draw(MyGameEngine::SpriteBatch& spriteBatch) {

	if (!m_isInit) {
		std::cout << "Tried to draw uninitialised sprite." << std::endl;
		return;
	}

	glm::vec4 rect = glm::vec4 (
		m_rectTransform[0] - m_rectTransform[2] / 2,
		m_rectTransform[1] - m_rectTransform[3] / 2,
		m_rectTransform[2],
		m_rectTransform[3]
	);
	glm::vec4 uv = glm::vec4(0, 0, 1, 1);

	spriteBatch.Draw(rect, uv, m_texture.id, 0, m_color);
}


void Sprite::Init(const std::string& path, const MyGameEngine::Color& color) {
	m_texture = MyGameEngine::ResourceManager::GetTexture(path);
	m_color = color;
	m_isInit = true;
}
