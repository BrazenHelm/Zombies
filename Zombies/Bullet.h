#pragma once

#include <MyGameEngine/SpriteBatch.h>

#include <vector>

#include "Actor.h"
#include "Transform.h"


class Bullet
{
public:
	Bullet(glm::vec2 pos, glm::vec2 dir, int damage, int speed);
	~Bullet();

	void Update(float deltaTime);
	void Draw(MyGameEngine::SpriteBatch& spriteBatch);

	bool CollideWithWorld(const std::vector<std::string>& levelData);
	bool CollideWith(Actor* actor);

private:
	Transform2D m_transform;
	Sprite		m_sprite;
	int m_damage;

	std::string BULLET_TEXTURE_PATH = "Textures/Pixel Adventure 1/Other/Dust Particle.png";
	int BULLET_SIZE = 8;
};

