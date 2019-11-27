#include "Human.h"

#include <iostream>

Human::Human() :
	Actor(ActorType::HUMAN) {
}


Human::Human(glm::vec2 position) :
	Actor(ActorType::HUMAN, position) {
}


Human::Human(glm::vec2 position, float size) :
	Actor(ActorType::HUMAN, position, size) {
}


Human::~Human() {
}


void Human::Update(Actor& nearestEnemy) {
	m_transform.MoveAwayFrom(nearestEnemy.transform().Position(), 1.5);
	if (m_transform.IsTouching(nearestEnemy.transform())) {
		// turn into a zombie
		std::cout << "brainsssss" << std::endl;
		SetType(ActorType::ZOMBIE);
	}
}