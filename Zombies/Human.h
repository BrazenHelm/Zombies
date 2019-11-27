#pragma once

#include "Actor.h"

class Human : public Actor
{
public:
	Human(glm::vec2 position);
	~Human();

	void Update();

};
