#pragma once

#include <glm/glm.hpp>

class Transform
{
public:
	Transform(glm::vec2 position = glm::vec2(0,0), float radius = 50);
	~Transform();

	void Update();

	float DistanceTo(const Transform& other) const;
	bool IsTouching(const Transform& other) const;

	void MoveTowards(glm::vec2 target, float speed);
	void MoveAwayFrom(glm::vec2 target, float speed);

	// Getters
	glm::vec2 Position()  const	{ return m_position; }
	glm::vec2 Direction() const	{ return m_direction; }
	glm::vec2 Velocity()  const	{ return m_direction * m_speed; }
	float Speed()		  const	{ return m_speed; }
	float Radius()		  const	{ return m_radius; }

private:
	glm::vec2	m_position;
	glm::vec2	m_direction;
	float		m_speed;
	float		m_radius;
};

