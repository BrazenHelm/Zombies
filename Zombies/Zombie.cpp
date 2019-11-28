#include "Zombie.h"


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

	MyGameEngine::Color green;
	green.r = 0;	green.g = 255;	green.b = 0;	green.a = 255;
	m_sprite.Init(ZOMBIE_TEXTURE_PATH, green);
}


void Zombie::Update() {

}

//void Zombie::Update(Actor& nearestEnemy) {
//	m_transform.MoveTowards(nearestEnemy.transform().Position(), 1);
//}

