#pragma once

#include <MyGameEngine/SpriteBatch.h>

#include "Sprite.h"
#include "Transform.h"

class Human;
class Zombie;

class Actor
{
public:
	Actor(glm::vec2 position = glm::vec2(0,0), float size = 16);
	virtual ~Actor();

	// Execute once every frame
	virtual void Update(std::vector<Human*>& humans, std::vector<Zombie*>& zombies) = 0;
	virtual void DoActorCollision(std::vector<Human*>& humans, std::vector<Zombie*>& zombies) = 0;
	void DoLevelCollision(const std::vector<std::string>& levelData);

	void Draw(MyGameEngine::SpriteBatch& spriteBatch);

	Transform2D&	Transform() { return m_transform; }

protected:
	Transform2D		m_transform;
	Sprite			m_sprite;
	float			m_moveSpeed;

private:
	void CollideWithTile(glm::vec2 tilePos);
};

