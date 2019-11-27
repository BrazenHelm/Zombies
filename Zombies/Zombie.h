#pragma once

#include "Actor.h"

class Zombie : public Actor
{
public:
	Zombie(glm::vec2 position);
	~Zombie();

	void Update();

};

