#pragma once

#include "Actor.h"

class Zombie : public Actor
{
public:
	Zombie();
	Zombie(glm::vec2 position);
	Zombie(glm::vec2 position, float size);
	~Zombie();

	//void Update(Actor& nearestEnemy);

};

