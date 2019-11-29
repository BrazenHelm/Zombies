#include "Player.h"

#include <SDL/SDL.h>


Player::Player() {
}


Player::Player(glm::vec2 position, MyGameEngine::InputManager* pInput) {
	Start(position, pInput);
}


Player::~Player() {
}



void Player::Start(glm::vec2 position, MyGameEngine::InputManager* pInput) {
	m_transform.SetPosition(position);
	m_moveSpeed = PLAYER_MOVE_SPEED;

	MyGameEngine::Color white;
	white.r = 255;	white.g = 255;	white.b = 255;	white.a = 255;
	m_sprite.Init(PLAYER_TEXTURE_PATH, white);

	m_pInput = pInput;
}


void Player::Update(std::vector<Actor*>& humans, std::vector<Actor*>& zombies) {
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
}


void Player::DoActorCollision(std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {

}