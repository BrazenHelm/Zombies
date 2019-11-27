#include "Transform.h"

#include <iostream>


Transform::Transform(glm::vec2 position /*= (0,0) */, float radius /*= 50*/) :
	m_position(position),
	m_direction(0),
	m_speed(0),
	m_radius(radius) {
}


Transform::~Transform() {
}


void Transform::Update() {
	m_position += Velocity();
}


float Transform::DistanceTo(const Transform& other) const {
	return glm::length(m_position - other.Position());
}


bool Transform::IsTouching(const Transform& other) const {
	return (DistanceTo(other) <= m_radius + other.Radius());
}


void Transform::MoveTowards(glm::vec2 target, float speed) {
	glm::vec2 dir = target - m_position;
	m_direction = glm::normalize(dir);
	m_speed = speed;
}


void Transform::MoveAwayFrom(glm::vec2 target, float speed) {
	glm::vec2 dir = m_position - target;
	m_direction = glm::normalize(dir);
	m_speed = speed;
}
