#pragma once

#include "Actor.h"

class Human : public Actor
{
public:
	Human();
	Human(glm::vec2 position);
	virtual ~Human();

	virtual void Start(glm::vec2 position);
	virtual bool Update(std::vector<Actor*>& humans, std::vector<Actor*>& zombies, float deltaTime);

protected:
	virtual void DoActorCollision(std::vector<Human*>& humans, std::vector<Zombie*>& zombies);

private:
	const float HUMAN_MOVE_SPEED = 69.0f;
	const int HUMAN_HP = 20;
	const std::string HUMAN_TEXTURE_PATH = "Textures/Pixel Adventure 1/Main Characters/Mask Dude/Jump (32x32).png";
	const float	HUMAN_FLEE_DISTANCE = 64.0f;
};
