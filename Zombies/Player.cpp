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

	MyGameEngine::Color white;
	white.r = 255;	white.g = 255;	white.b = 255;	white.a = 255;
	m_sprite.Init(PLAYER_TEXTURE_PATH, white);

	m_pInput = pInput;
	m_pCamera = pCamera;

	AddGun(new Gun("Magnum",	 25,  1,  2.5f, 20, 50));
	AddGun(new Gun("Shotgun",	 45, 10, 15.0f, 20, 15));
	AddGun(new Gun("MP5",		  5,  1,  5.0f, 20,  8));
}


bool Player::Update(std::vector<Actor*>& humans, std::vector<Actor*>& zombies, std::vector<Bullet>& bullets) {

	if (m_hp <= 0) return true;

	glm::vec2 direction = glm::vec2(0,0);
	if (m_pInput->IsKeyPressed(SDLK_w)) { direction += glm::vec2( 0, 1); }
	if (m_pInput->IsKeyPressed(SDLK_a)) { direction += glm::vec2(-1, 0); }
	if (m_pInput->IsKeyPressed(SDLK_s)) { direction += glm::vec2( 0,-1); }
	if (m_pInput->IsKeyPressed(SDLK_d)) { direction += glm::vec2( 1, 0); }

	if (direction == glm::vec2(0, 0)) {
		m_transform.Stop();
	}
	else {
		m_transform.MoveInDirection(direction, m_moveSpeed);
	}
	m_transform.Update();

	static bool keyDown1 = false;
	static bool keyDown2 = false;
	static bool keyDown3 = false;

	if (m_pInput->IsKeyPressed(SDLK_1) && m_pGuns.size() >= 1 && !keyDown1) {
		m_equippedGun = 0;
		std::cout << "Equipped " << m_pGuns[0]->Name() << std::endl;
		keyDown1 = true;
	}
	if (m_pInput->IsKeyPressed(SDLK_2) && m_pGuns.size() >= 2 && !keyDown2) {
		m_equippedGun = 1;
		std::cout << "Equipped " << m_pGuns[1]->Name() << std::endl;
		keyDown2 = true;
	}
	if (m_pInput->IsKeyPressed(SDLK_3) && m_pGuns.size() >= 3 && !keyDown3) {
		m_equippedGun = 2;
		std::cout << "Equipped " << m_pGuns[2]->Name() << std::endl;
		keyDown3 = true;
	}
	if (!m_pInput->IsKeyPressed(SDLK_1)) keyDown1 = false;
	if (!m_pInput->IsKeyPressed(SDLK_2)) keyDown2 = false;
	if (!m_pInput->IsKeyPressed(SDLK_3)) keyDown3 = false;

	if (m_equippedGun != -1) {
		if (m_pInput->IsKeyPressed(SDL_BUTTON_LEFT)) {
			glm::vec2 mousePos = m_pCamera->ScreenToWorldPosition(m_pInput->MousePosition());
			glm::vec2 mouseDir = glm::normalize(mousePos - m_transform.Position());
			m_pGuns[m_equippedGun]->Update(true, m_transform.Position(), mouseDir, bullets);
		}
		else {
			glm::vec2 dir = glm::vec2(1, 0);
			m_pGuns[m_equippedGun]->Update(false, m_transform.Position(), dir, bullets);
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