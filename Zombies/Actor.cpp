#include "Actor.h"

#include <ctime>
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
		if (intCornerPos.x < 0 || intCornerPos.y < 0 || intCornerPos.x >= levelData[0].size() || intCornerPos.y >= levelData.size()) {
			std::cout << "OUT OF BOUNDS" << std::endl;
			return;
		}

		if (levelData[(int)intCornerPos.y][(int)intCornerPos.x] == 'w') {		// only collide with walls
			tileCollisions.push_back((intCornerPos + glm::vec2(0.5, 0.5)) * tileSize);
		}
	}

	for (glm::vec2 collison : tileCollisions) {
		CollideWithTile(collison);
	}
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
		// send off in a new direction. stops actors from wall-hugging
		m_transform.MoveInDirection(glm::normalize(GetRandomDirection()), m_moveSpeed);
	}
}


void Actor::Draw(MyGameEngine::SpriteBatch& spriteBatch) {
	glm::vec2 dimensions{ m_transform.Radius(), m_transform.Radius() };
	m_sprite.Draw(spriteBatch, m_transform.Position(), dimensions);
}


glm::vec2 Actor::GetRandomDirection() {
	static std::mt19937 rng;
	static std::uniform_real_distribution<float> angle(0.0f, 2 * (float)std::_Pi);
	float randomAngle = angle(rng);
	return glm::vec2(cos(randomAngle), sin(randomAngle));
}


bool Actor::CollideWith(Actor* other) {

	if (other == this) return false;

	glm::vec2 relativePosition = m_transform.Position() - other->Transform().Position();
	// this is a hacky way to avoid problems that occur when actors spawn in the same position
	if (relativePosition == glm::vec2(0, 0)) {
		relativePosition = glm::vec2(1, 0);
	}
	float touchDistance = m_transform.Radius() + other->Transform().Radius();
	float depth = touchDistance - glm::length(relativePosition);

	if (depth > 0) {
		glm::vec2 vecToMove = glm::normalize(relativePosition) * depth / 2.0f;
		m_transform.SetRelativePosition(vecToMove);
		other->Transform().SetRelativePosition(-vecToMove);
		return true;
	}
	else {
		return false;
	}
}


Actor* Actor::GetNearest(std::vector<Actor*>& actors) {

	if (actors.size() == 0) return nullptr;

	Actor* nearest = actors[0];
	float minDistance = m_transform.DistanceTo(actors[0]->Transform());

	for (size_t i = 1; i < actors.size(); i++) {
		float distance = m_transform.DistanceTo(actors[i]->Transform());
		if (distance < minDistance) {
			minDistance = distance;
			nearest = actors[i];
		}
	}

	return nearest;
}

