#include "Zombie.h"


Zombie::Zombie() :
	Actor(ActorType::ZOMBIE) {
}


Zombie::Zombie(glm::vec2 position) :
	Actor(ActorType::ZOMBIE, position) {
}


Zombie::Zombie(glm::vec2 position, float size) :
	Actor(ActorType::ZOMBIE, position, size) {
}


Zombie::~Zombie() {
}


void Zombie::Update(Actor& nearestEnemy) {
	m_transform.MoveTowards(nearestEnemy.transform().Position(), 1);
}

