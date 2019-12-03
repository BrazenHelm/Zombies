#include "Player.h"

#include <SDL/SDL.h>

#include <iostream>


Player::Player() :
	m_pGuns(),
	m_equippedGun(-1) {
}


Player::Player(glm::vec2 position, MyGameEngine::InputManager* pInput, MyGameEngine::Camera2D* pCamera) {
	Start(position, pInput, pCamera);
}


Player::~Player() {
}


void Player::Start(glm::vec2 position, MyGameEngine::InputManager* pInput, MyGameEngine::Camera2D* pCamera) {
	m_transform.SetPosition(position);
	m_moveSpeed = PLAYER_MOVE_SPEED;
	m_hp = PLAYER_HP;

	MyGameEngine::Color white(255, 255, 255, 255);
	m_sprite.Init(PLAYER_TEXTURE_PATH, white);

	m_pInput = pInput;
	m_pCamera = pCamera;

	AddGun(new Gun("Magnum",	 0.42f,  1,  2.5f, 1200.0f, 50));
	AddGun(new Gun("Shotgun",	 0.75f, 10, 15.0f, 1200.0f, 15));
	AddGun(new Gun("MP5",		 0.08f,  1,  5.0f, 1200.0f,  8));
}


bool Player::Update(std::vector<Actor*>& humans, std::vector<Actor*>& zombies, std::vector<Bullet>& bullets, float deltaTime) {

	if (m_hp <= 0) return true;

	glm::vec2 direction = glm::vec2(0,0);
	if (m_pInput->KeyHeld(SDLK_w)) { direction += glm::vec2( 0, 1); }
	if (m_pInput->KeyHeld(SDLK_a)) { direction += glm::vec2(-1, 0); }
	if (m_pInput->KeyHeld(SDLK_s)) { direction += glm::vec2( 0,-1); }
	if (m_pInput->KeyHeld(SDLK_d)) { direction += glm::vec2( 1, 0); }

	if (direction == glm::vec2(0, 0)) {
		m_transform.Stop();
	}
	else {
		m_transform.MoveInDirection(direction, m_moveSpeed);
	}
	m_transform.Update(deltaTime);

	if (m_pInput->KeyDown(SDLK_1)) { EquipGun(0); }
	if (m_pInput->KeyDown(SDLK_2)) { EquipGun(1); }
	if (m_pInput->KeyDown(SDLK_3)) { EquipGun(2); }

	if (m_equippedGun != -1) {
		if (m_pInput->KeyHeld(SDL_BUTTON_LEFT)) {
			glm::vec2 mousePos = m_pCamera->ScreenToWorldPosition(m_pInput->MousePosition());
			glm::vec2 mouseDir = glm::normalize(mousePos - m_transform.Position());
			m_pGuns[m_equippedGun]->Update(true, m_transform.Position(), mouseDir, bullets, deltaTime);
		}
		else {
			glm::vec2 dir = glm::vec2(1, 0);
			m_pGuns[m_equippedGun]->Update(false, m_transform.Position(), dir, bullets, deltaTime);
		}
	}

	return false;
}


void Player::AddGun(Gun* pGun) {
	m_pGuns.push_back(pGun);
	if (m_equippedGun == -1) m_equippedGun = 0;
}


void Player::DoActorCollision(std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {
	// not implemented
}


void Player::EquipGun(size_t index) {
	if (m_pGuns.size() <= index) return;
	m_equippedGun = index;
	std::cout << "Equipped " << m_pGuns[index]->Name() << std::endl;
}