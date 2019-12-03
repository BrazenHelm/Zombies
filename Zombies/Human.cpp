#include "Human.h"

#include "Zombie.h"

Human::Human() {
}


Human::Human(glm::vec2 position) {
	Start(position);
}


Human::~Human() {
}


void Human::Start(glm::vec2 position) {
	m_transform.SetPosition(position);
	m_moveSpeed = HUMAN_MOVE_SPEED;
	m_hp = HUMAN_HP;

	MyGameEngine::Color white(255, 255, 255, 255);
	m_sprite.Init(HUMAN_TEXTURE_PATH, white);

	m_transform.MoveInDirection(glm::normalize(GetRandomDirection()), m_moveSpeed);
}


bool Human::Update(std::vector<Actor*>& humans, std::vector<Actor*>& zombies, float deltaTime) {

	if (m_hp <= 0) return true;

	Actor* nearest = GetNearest(zombies);
	if (nearest != nullptr && m_transform.DistanceTo(nearest->Transform()) < HUMAN_FLEE_DISTANCE) {
		m_transform.MoveAwayFrom(nearest->Transform().Position(), m_moveSpeed);
	}
	else {
		static int frameCounter = 0;
		if (frameCounter++ == 60) {
			m_transform.MoveInDirection(glm::normalize(GetRandomDirection()), m_moveSpeed);
			frameCounter = 0;
		}
	}
	m_transform.Update(deltaTime);

	return false;
}


void Human::DoActorCollision(std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {
	// not implemented
}
