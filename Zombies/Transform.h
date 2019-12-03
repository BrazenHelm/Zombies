#pragma once

#include <glm/glm.hpp>
#include <MyGameEngine/Time.h>

class Transform2D
{
public:
	Transform2D(glm::vec2 position = glm::vec2(0,0), float radius = 16);
	~Transform2D();

	void Update(float deltaTime);

	void SetPosition(glm::vec2 target);
	void SetRelativePosition(glm::vec2 target);
	void MoveTowards(glm::vec2 target, float speed);
	void MoveAwayFrom(glm::vec2 target, float speed);
	void MoveInDirection(glm::vec2 dir, float speed);
	void Stop();

	// Getters
	float DistanceTo(const Transform2D& other) const;
	glm::vec2 Position()	const	{ return m_position; }
	glm::vec2 Direction()	const	{ return m_direction; }
	glm::vec2 Velocity()	const	{ return m_direction * m_speed; }
	float Speed()			const	{ return m_speed; }
	float Radius()			const	{ return m_radius; }

private:
	glm::vec2		m_position;
	glm::vec2		m_direction;
	float			m_speed;
	float			m_radius;
};

