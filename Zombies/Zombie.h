#pragma once

#include "Actor.h"

class Zombie : public Actor
{
public:
	Zombie();
	Zombie(glm::vec2 position);
	~Zombie();

	void Start(glm::vec2 position);
	bool Update(std::vector<Actor*>& humans, std::vector<Actor*>& zombies);

	static int Damage() { return ZOMBIE_DAMAGE; }

protected:
	void DoActorCollision(std::vector<Human*>& humans, std::vector<Zombie*>& zombies);

private:
	const float ZOMBIE_MOVE_SPEED = 1.25f;
	const int ZOMBIE_HP = 80;
	static constexpr int ZOMBIE_DAMAGE = 10;
	const std::string ZOMBIE_TEXTURE_PATH = "Textures/Pixel Adventure 1/Main Characters/Mask Dude/Jump (32x32).png";
	const float ZOMBIE_CHASE_DISTANCE = 320.0f;

	//Human* getNearestHuman(std::vector<Human*>& humans);
};

