#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "Bullet.h"


class Gun
{
public:
	Gun(std::string name, float rateOfFire, int pellets, float spread, float speed, int damage);
	~Gun();

	void Update(bool mouseHeld, const glm::vec2& pos, glm::vec2& dir, std::vector<Bullet>& bullets, float deltaTime);

	std::string Name() { return m_name; }

private:
	void Fire(const glm::vec2& pos, const glm::vec2& dir, std::vector<Bullet>& bullets);

	std::string m_name;
	float m_rateOfFire;	//< seconds per shot
	int m_pellets;		//< per shot
	float m_spread;		//< in radians; pass in value in degrees
	float m_speed;		//< bullet speed
	int m_damage;		//< bullet damage
};

