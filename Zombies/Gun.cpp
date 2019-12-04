#include "Gun.h"

#include <cmath>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>
#include <random>
#include <iostream>

Gun::Gun(std::string name, float rateOfFire, int pellets, float spread, float speed, int damage, MyGameEngine::Audio::SoundEffect sfx) :
	m_name(name),
	m_rateOfFire(rateOfFire),
	m_pellets(pellets),
	m_spread(spread * ((float)std::_Pi / 180.0f)),	// convert degrees to radians
	m_speed(speed),
	m_damage(damage),
	m_sfx(sfx) {
}


Gun::~Gun() {
}


void Gun::Update(bool mouseHeld, const glm::vec2& pos, glm::vec2& dir, std::vector<Bullet>& bullets, float deltaTime) {
	static float timeSinceFired = 0;
	timeSinceFired += deltaTime;
	if (timeSinceFired > m_rateOfFire && mouseHeld) {
		Fire(pos, dir, bullets);
		timeSinceFired = 0;
	}
}


void Gun::Fire(const glm::vec2& pos, const glm::vec2& dir, std::vector<Bullet>& bullets) {

	m_sfx.play();

	static std::mt19937 rng((size_t)time(nullptr));
	std::uniform_real_distribution<float> randomSpread(-m_spread, m_spread);

	for (int i = 0; i < m_pellets; i++) {
		float randomAngle = randomSpread(rng);
		glm::vec2 spreadDir = glm::rotate(dir, randomAngle);
		bullets.emplace_back(pos, spreadDir, m_damage, m_speed);
	}
}