#pragma once

#include <glm/glm.hpp>

class Transform
{
public:
	Transform();
	~Transform();

private:
	glm::vec2	m_position;
	glm::vec2	m_direction;
	float		m_speed;
	float		m_radius;
};

