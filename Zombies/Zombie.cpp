#include "Zombie.h"

#include <iostream>

#include "Human.h"


Zombie::Zombie() {
}


Zombie::Zombie(glm::vec2 position) {
	Start(position);
}


Zombie::~Zombie() {
}


void Zombie::Start(glm::vec2 position) {
	m_transform.SetPosition(position);
	m_moveSpeed = ZOMBIE_MOVE_SPEED;
	m_hp = ZOMBIE_HP;

	MyGameEngine::Color orange(255, 165, 0, 255);
	m_sprite.Init(ZOMBIE_TEXTURE_PATH, orange);

	m_transform.MoveInDirection(glm::normalize(GetRandomDirection()), m_moveSpeed);
}


bool Zombie::Update(std::vector<Actor*>& humans, std::vector<Actor*>& zombies) {

	if (m_hp <= 0) return true;

	Actor* nearest = GetNearest(humans);
	if (nearest != nullptr && m_transform.DistanceTo(nearest->Transform()) < ZOMBIE_CHASE_DISTANCE) {
		m_transform.MoveTowards(nearest->Transform().Position(), m_moveSpeed);
	}
	else {
		static int frameCounter = 0;
		if (frameCounter++ == 60) {
			m_transform.MoveInDirection(glm::normalize(GetRandomDirection()), m_moveSpeed);
			frameCounter = 0;
		}
	}
	m_transform.Update();

	return false;
}


void Zombie::DoActorCollision(std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {
	// not implemented
}


//Human* Zombie::getNearestHuman(std::vector<Human*>& humans) {
//
//	if (humans.size() == 0) return nullptr;
//
//	Human* nearestHuman = humans[0];
//	float minDistance = m_transform.DistanceTo(humans[0]->Transform());
//
//	for (int i = 1; i < humans.size(); i++) {
//		float distance = m_transform.DistanceTo(humans[i]->Transform());
//		if (distance < minDistance) {
//			minDistance = distance;
//			nearestHuman = humans[i];
//		}
//	}
//
//	return nearestHuman;
//}