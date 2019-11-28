#include "Human.h"

#include <iostream>

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

	MyGameEngine::Color white;
	white.r = 255;	white.g = 255;	white.b = 255;	white.a = 255;
	m_sprite.Init(HUMAN_TEXTURE_PATH, white);
}


void Human::Update(std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {

}


void Human::DoActorCollision(std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {

}


//void Human::Update(Actor& nearestEnemy) {
//	m_transform.MoveAwayFrom(nearestEnemy.transform().Position(), 1.5);
//	if (m_transform.IsTouching(nearestEnemy.transform())) {
//		// turn into a zombie
//		std::cout << "brainsssss" << std::endl;
//		SetType(ActorType::ZOMBIE);
//		// TODO: this does not work! pointer is still of type Human* and so actor still behaves like a human (runs away from enemies)
//	}
//}