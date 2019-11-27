#include "Actor.h"

Actor::Actor(glm::vec2 position, float size) :
	m_transform(position, size),
	m_sprite(position, glm::vec2(2*size, 2*size)) {
}


void Actor::Draw(MyGameEngine::SpriteBatch& spriteBatch) {
	m_sprite.Draw(spriteBatch);
}
