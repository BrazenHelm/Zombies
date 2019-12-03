#include "Bullet.h"
#include <iostream>

#include "Level.h"

Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, int damage, int speed) :
	m_transform(pos), m_damage(damage) {
	m_transform.MoveInDirection(dir, (float)speed);

	MyGameEngine::Color red (128, 0, 0, 255);
	m_sprite.Init(BULLET_TEXTURE_PATH, red);
}


Bullet::~Bullet() {
}


void Bullet::Update(float deltaTime) {
	m_transform.Update(deltaTime);
}


void Bullet::Draw(MyGameEngine::SpriteBatch& spriteBatch) {
	m_sprite.Draw(spriteBatch, m_transform.Position(), glm::vec2(BULLET_SIZE, BULLET_SIZE));
}


bool Bullet::CollideWithWorld(const std::vector<std::string>& levelData) {
	glm::ivec2 tilePos{ floor(m_transform.Position().x / Level::TILE_SIZE),
						floor(m_transform.Position().y / Level::TILE_SIZE) };
	if (tilePos.x < 0 || (size_t)tilePos.x >= levelData[0].size() ||
		tilePos.y < 0 || (size_t)tilePos.y >= levelData.size())
		return true;
	if (levelData[tilePos.y][tilePos.x] == 'w')
		return true;
	return false;
}


bool Bullet::CollideWith(Actor* actor) {
	float distance = m_transform.DistanceTo(actor->Transform());
	if (distance < actor->Transform().Radius()) {
		actor->TakeDamage(m_damage);
		return true;
	}
	return false;
}