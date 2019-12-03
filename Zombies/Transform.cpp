#include "Transform.h"

#include <iostream>


Transform2D::Transform2D(glm::vec2 position /*= (0,0) */, float radius /*= 16*/) :
	m_position(position),
	m_direction(0),
	m_speed(0),
	m_radius(radius) {
}


Transform2D::~Transform2D() {
}


void Transform2D::Update(float deltaTime) {
	m_position += Velocity() * deltaTime;
}


float Transform2D::DistanceTo(const Transform2D& other) const {
	return glm::length(m_position - other.Position());
}


void Transform2D::SetPosition(glm::vec2 target) {
	m_position = target;
}


void Transform2D::SetRelativePosition(glm::vec2 target) {
	SetPosition(m_position + target);
}


void Transform2D::MoveTowards(glm::vec2 target, float speed) {
	glm::vec2 dir = target - m_position;
	m_direction = glm::normalize(dir);
	m_speed = speed;
}


void Transform2D::MoveAwayFrom(glm::vec2 target, float speed) {
	glm::vec2 dir = m_position - target;
	m_direction = glm::normalize(dir);
	m_speed = speed;
}


void Transform2D::MoveInDirection(glm::vec2 dir, float speed) {
	m_direction = glm::normalize(dir);
	m_speed = speed;
}


void Transform2D::Stop() {
	m_speed = 0;
}

