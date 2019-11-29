#include "Human.h"

#include "Zombie.h"

Human::Human() {
}


Human::Human(glm::vec2 position) {
	Start(position);
}


Human::~Human() {
}


void Human::Start(glm::vec2 position) {
	m_transform.SetPosition(position);
	m_moveSpeed = HUMAN_MOVE_SPEED;

	MyGameEngine::Color white;
	white.r = 255;	white.g = 255;	white.b = 255;	white.a = 255;
	m_sprite.Init(HUMAN_TEXTURE_PATH, white);

	m_transform.MoveInDirection(glm::normalize(GetRandomDirection()), m_moveSpeed);
}


void Human::Update(std::vector<Actor*>& humans, std::vector<Actor*>& zombies) {
	//Actor* nearest = GetNearest(zombies);
	//if (nearest != nullptr && m_transform.DistanceTo(nearest->Transform()) < HUMAN_FLEE_DISTANCE) {
	//	m_transform.MoveAwayFrom(nearest->Transform().Position(), m_moveSpeed);
	//}
	//else {
		static int frameCounter = 0;
		if (frameCounter++ == 60) {
			m_transform.MoveInDirection(glm::normalize(GetRandomDirection()), m_moveSpeed);
			frameCounter = 0;
		}
	//}
	m_transform.Update();
}


void Human::DoActorCollision(std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {
	// not implemented
}
