#pragma once

#include <MyGameEngine/SpriteBatch.h>

#include "Sprite.h"
#include "Transform.h"

enum class ActorType { HUMAN, ZOMBIE };

class Actor
{
public:
	Actor(ActorType type, glm::vec2 position = glm::vec2(0,0), float size = 50);
	~Actor() = default;

	void SetType(ActorType newType);

	// Execute once every frame
	void Update(Actor& nearestEnemy);

	void Draw(MyGameEngine::SpriteBatch& spriteBatch);

	ActorType Type() { return m_type; }
	Transform& transform() { return m_transform; }

protected:
	ActorType	m_type;
	Transform	m_transform;
	Sprite		m_sprite;
};

