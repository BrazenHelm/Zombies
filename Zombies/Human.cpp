#include "Human.h"


Human::Human(glm::vec2 position) :
	Actor(position, 30)
{
	MyGameEngine::Color white;
	white.r = 255;	white.g = 255;	white.b = 255;	white.a = 255;
	m_sprite.Init("Textures/Pixel Adventure 1/Main Characters/Mask Dude/Jump (32x32).png", white);
}


Human::~Human() {
}


void Human::Update() {
	// do nothing
}