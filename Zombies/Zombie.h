#pragma once

#include "Actor.h"

class Zombie : public Actor
{
public:
	Zombie();
	Zombie(glm::vec2 position);
	~Zombie();

	void Start(glm::vec2 position);
	void Update();

private:
	const float ZOMBIE_MOVE_SPEED = 1.5f;
	const std::string ZOMBIE_TEXTURE_PATH = "Textures/Pixel Adventure 1/Main Characters/Mask Dude/Jump (32x32).png";
};

