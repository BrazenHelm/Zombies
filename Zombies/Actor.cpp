#include "Actor.h"

#include <iostream>


Actor::Actor(ActorType type, glm::vec2 position /*= (0,0)*/, float size /*= 50*/) :
	m_transform(position, size) {
	SetType(type);
}


void Actor::SetType(ActorType newType) {

	m_type = newType;

	MyGameEngine::Color color;
	std::string texturePath;

	switch (newType) {

		case ActorType::HUMAN:
			color.r = 255;	color.g = 255;	color.b = 255;	color.a = 255;
			texturePath = "Textures/Pixel Adventure 1/Main Characters/Mask Dude/Jump (32x32).png";
			break;

		case ActorType::ZOMBIE:
			color.r = 000;	color.g = 255;	color.b = 000;	color.a = 255;
			texturePath = "Textures/Pixel Adventure 1/Main Characters/Mask Dude/Jump (32x32).png";
			break;
	}

	m_sprite.Init(texturePath, color);
}


void Actor::Draw(MyGameEngine::SpriteBatch& spriteBatch) {
	glm::vec2 dimensions{ m_transform.Radius(), m_transform.Radius() };
	m_sprite.Draw(spriteBatch, m_transform.Position(), dimensions);
}

