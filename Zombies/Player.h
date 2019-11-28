#pragma once

#include <MyGameEngine/InputManager.h>

#include "Human.h"

class Player : public Human
{
public:
	Player();
	Player(glm::vec2 position, MyGameEngine::InputManager* pInput);
	~Player();

	void Start(glm::vec2 position, MyGameEngine::InputManager* pInput);
	void Update(std::vector<Human*>& humans, std::vector<Zombie*>& zombies);
	void DoActorCollision(std::vector<Human*>& humans, std::vector<Zombie*>& zombies);

private:
	const float PLAYER_MOVE_SPEED = 3.0f;
	const std::string PLAYER_TEXTURE_PATH = "Textures/Pixel Adventure 1/Main Characters/Ninja Frog/Jump (32x32).png";

	MyGameEngine::InputManager* m_pInput;

};

