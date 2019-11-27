#pragma once

#include "Actor.h"

class Human : public Actor
{
public:
	Human();
	Human(glm::vec2 position);
	Human(glm::vec2 position, float size);
	~Human();

	//void Update(Actor& nearestEnemy);

};
