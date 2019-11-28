#pragma once

#include <MyGameEngine/SpriteBatch.h>

#include "Sprite.h"
#include "Transform.h"

class Actor
{
public:
	Actor(glm::vec2 position = glm::vec2(0,0), float size = 16);
	virtual ~Actor();

	// Execute once every frame
	virtual void Update() = 0;

	void Draw(MyGameEngine::SpriteBatch& spriteBatch);

	Transform2D&	Transform() { return m_transform; }

protected:
	Transform2D		m_transform;
	Sprite			m_sprite;
	float			m_moveSpeed;
};

