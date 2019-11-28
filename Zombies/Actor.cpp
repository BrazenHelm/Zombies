#include "Actor.h"

#include <iostream>

#include "Level.h"

Actor::Actor(glm::vec2 position /*= (0,0)*/, float size /*= 50*/) :
	m_transform(position, size) {
}


Actor::~Actor() {
}


void Actor::DoLevelCollision(const std::vector<std::string>& levelData) {

	std::vector<glm::vec2> tileCollisions;	// all the tiles this agent is colliding with

	glm::vec2 pos = m_transform.Position();
	float radius = m_transform.Radius();
	float tileSize = static_cast<float>(Level::TILE_SIZE);
	std::vector<glm::vec2> offsets{ {-1,-1}, {-1, 1}, { 1,-1}, { 1, 1} };

	for (glm::vec2 offset : offsets) {
		glm::vec2 cornerPos = (pos + offset * radius) / tileSize;
		glm::vec2 intCornerPos = glm::vec2(floor(cornerPos.x), floor(cornerPos.y));
		if (levelData[(int)intCornerPos.y][(int)intCornerPos.x] == 'w') {		// only collide with walls
			std::cout << "collision with coordinates " << intCornerPos.x << " " << intCornerPos.y << std::endl;
			tileCollisions.push_back((intCornerPos + glm::vec2(0.5, 0.5)) * tileSize);
		}
	}

	for (glm::vec2 collison : tileCollisions) {
		CollideWithTile(collison);
	}
}


void Actor::Draw(MyGameEngine::SpriteBatch& spriteBatch) {
	glm::vec2 dimensions{ m_transform.Radius(), m_transform.Radius() };
	m_sprite.Draw(spriteBatch, m_transform.Position(), dimensions);
}


// AABB collision
void Actor::CollideWithTile(glm::vec2 tilePos) {

	glm::vec2 relativePos = m_transform.Position() - tilePos;
	float collisionRadius = m_transform.Radius() + Level::TILE_SIZE / 2;

	int xSign = (relativePos.x > 0) - (relativePos.x < 0);
	int ySign = (relativePos.y > 0) - (relativePos.y < 0);

	float xDepth = collisionRadius - abs(relativePos.x);
	float yDepth = collisionRadius - abs(relativePos.y);

	if (xDepth > 0 || yDepth > 0) {		// if a collision occured
		if (xDepth > yDepth) {
			m_transform.SetRelativePosition(glm::vec2(0, ySign * yDepth));
		}
		else {
			m_transform.SetRelativePosition(glm::vec2(xSign * xDepth, 0));
		}
	}
}
