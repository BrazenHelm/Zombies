#pragma once

#include "Actor.h"

class Human : public Actor
{
public:
	Human();
	Human(glm::vec2 position);
	virtual ~Human();

	virtual void Start(glm::vec2 position);
	virtual void Update();

private:
	const float HUMAN_MOVE_SPEED = 2.0f;
	const std::string HUMAN_TEXTURE_PATH = "Textures/Pixel Adventure 1/Main Characters/Mask Dude/Jump (32x32).png";
};
