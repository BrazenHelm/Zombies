#pragma once

#include <MyGameEngine/Camera2D.h>
#include <MyGameEngine/InputManager.h>

#include "Gun.h"
#include "Human.h"

class Player : public Human
{
public:
	Player();
	Player(glm::vec2 position, MyGameEngine::InputManager* pInput, MyGameEngine::Camera2D* pCamera);
	~Player();

	void Start(glm::vec2 position, MyGameEngine::InputManager* pInput, MyGameEngine::Camera2D* pCamera);
	bool Update(std::vector<Actor*>& humans, std::vector<Actor*>& zombies, std::vector<Bullet>& bullets, float deltaTime);

	void Draw(MyGameEngine::SpriteBatch& spriteBatch) override;

	void AddGun(Gun* pGun);

protected:
	void DoActorCollision(std::vector<Human*>& humans, std::vector<Zombie*>& zombies);

private:
	const float PLAYER_MOVE_SPEED = 180.0f;
	const int PLAYER_HP = 50;
	const std::string PLAYER_TEXTURE_PATH = "Textures/Pixel Adventure 1/Main Characters/Ninja Frog/Jump (32x32).png";

	MyGameEngine::InputManager* m_pInput;
	MyGameEngine::Camera2D* m_pCamera;

	std::vector<Gun*> m_pGuns;
	int m_equippedGun;

	void EquipGun(size_t index);

};

