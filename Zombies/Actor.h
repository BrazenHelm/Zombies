#pragma once

#include <MyGameEngine/SpriteBatch.h>

#include "Sprite.h"
#include "Transform.h"

class Actor
{
public:
	Actor(glm::vec2 position, float size);
	~Actor() = default;

	// Executes once every frame
	virtual void Update() = 0;

	void Draw(MyGameEngine::SpriteBatch& spriteBatch);

protected:
	Transform	m_transform;
	Sprite		m_sprite;
};

