#include "Zombie.h"

#include <MyGameEngine/ResourceManager.h>

#include <iostream>

Zombie::Zombie(glm::vec2 position) :
	Actor(position, 50)
{
	MyGameEngine::Color green;
	green.r = 0;	green.g = 255;	green.b = 0;	green.a = 255;
	m_sprite.Init("Textures/Pixel Adventure 1/Main Characters/Mask Dude/Jump (32x32).png", green);
	//Init("Textures/Pixel Adventure 1/Items/Boxes/Box1/Idle.png", position, glm::vec2(100, 100));
}


Zombie::~Zombie() {
}

//void Zombie::Draw(MyGameEngine::SpriteBatch& spriteBatch) {
//
//	if (!m_isInit) {
//		std::cout << "Tried to draw uninitialised sprite." << std::endl;
//		return;
//	}
//
//	glm::vec4 rect = glm::vec4(
//		m_rectTransform[0] - m_rectTransform[2] / 2,
//		m_rectTransform[1] - m_rectTransform[3] / 2,
//		m_rectTransform[2],
//		m_rectTransform[3]
//	);
//	glm::vec4 uv = glm::vec4(0, 0, 1, 1);
//	MyGameEngine::Color white;
//	white.r = 255;	white.g = 255;	white.b = 255;	white.a = 255;
//
//	spriteBatch.Draw(rect, uv, m_texture.id, 0, white);
//}


//void Zombie::Draw(MyGameEngine::SpriteBatch& spriteBatch) {
//	m_sprite.Draw(spriteBatch);
//}


//void Zombie::Init(const std::string& path, const glm::vec2& position, const glm::vec2& dimensions) {
//	m_texture = MyGameEngine::ResourceManager::GetTexture(path);
//	m_rectTransform = glm::vec4(position.x, position.y, dimensions.x, dimensions.y);
//	m_isInit = true;
//}


