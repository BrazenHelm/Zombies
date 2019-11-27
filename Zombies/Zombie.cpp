#include "Zombie.h"


Zombie::Zombie(glm::vec2 position) :
	Actor(position, 50)
{
	MyGameEngine::Color green;
	green.r = 0;	green.g = 255;	green.b = 0;	green.a = 255;
	m_sprite.Init("Textures/Pixel Adventure 1/Main Characters/Mask Dude/Jump (32x32).png", green);
}


Zombie::~Zombie() {
}


void Zombie::Update() {
	// do nothing
}

