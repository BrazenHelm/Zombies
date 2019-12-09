#pragma once

#include <MyGameEngine/SpriteBatch.h>

#include <iostream>
#include <random>

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
	virtual bool Update(std::vector<Actor*>& humans, std::vector<Actor*>& zombies, float deltaTime) = 0;

			void DoLevelCollision(const std::vector<std::string>& levelData);
			bool CollideWith(Actor* other);
private:	void CollideWithTile(glm::vec2 tilePos);
public:		
	virtual void Draw(MyGameEngine::SpriteBatch& spriteBatch);

			void TakeDamage(int damage) { m_hp -= damage; }

	Transform2D&	Transform() { return m_transform; }

protected:
	Transform2D		m_transform;
	Sprite			m_sprite;
	float			m_moveSpeed;
	int				m_hp;

	static glm::vec2 GetRandomDirection();

	virtual void DoActorCollision(std::vector<Human*>& humans, std::vector<Zombie*>& zombies) = 0;

	Actor* GetNearest(std::vector<Actor*>& actors);

};

