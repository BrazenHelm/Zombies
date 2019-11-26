#include "Bullet.h"


#include <MyGameEngine/ResourceManager.h>


Bullet::Bullet(int lifetime, float speed, glm::vec2 direction, glm::vec2 position) :
	m_lifetime(lifetime),
	m_speed(speed),
	m_direction(direction),
	m_position(position) {
}


Bullet::~Bullet() {
}


void Bullet::Draw(MyGameEngine::SpriteBatch& spriteBatch) {

	MyGameEngine::Color color;
	color.r = 255; color.g = 255; color.b = 255; color.a = 255;
	glm::vec4 pos = glm::vec4(m_position.x, m_position.y, 30, 30);
	glm::vec4 uv{ 0, 0, 1, 1 };
	static MyGameEngine::GLTexture texture = MyGameEngine::ResourceManager::GetTexture("Textures/Pixel Adventure 1/Items/Boxes/Box1/Idle.png");

	spriteBatch.Draw(pos, uv, texture.id, 0, color);
}

bool Bullet::Update() {

	m_position += m_direction * m_speed;
	if (m_lifetime-- <= 0) return true;
	else return false;
}