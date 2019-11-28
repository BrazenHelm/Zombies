#include "Actor.h"

#include <iostream>


Actor::Actor(glm::vec2 position /*= (0,0)*/, float size /*= 50*/) :
	m_transform(position, size) {
}


Actor::~Actor() {
}


void Actor::Draw(MyGameEngine::SpriteBatch& spriteBatch) {
	glm::vec2 dimensions{ m_transform.Radius(), m_transform.Radius() };
	m_sprite.Draw(spriteBatch, m_transform.Position(), dimensions);
}

