#pragma once

#include <MyGameEngine/SpriteBatch.h>

#include <glm/glm.hpp>

class Bullet
{
public:
	Bullet(int lifetime, float speed, glm::vec2 direction, glm::vec2 position);
	~Bullet();

	void Draw(MyGameEngine::SpriteBatch& spriteBatch);
	bool Update();

private:
	int m_lifetime;
	float m_speed;
	glm::vec2 m_direction;
	glm::vec2 m_position;
};

