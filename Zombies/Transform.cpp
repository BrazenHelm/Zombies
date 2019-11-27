#include "Transform.h"



Transform::Transform(glm::vec2 position, float radius /*= 50*/) :
	m_position(position),
	m_direction(0),
	m_speed(0),
	m_radius(radius) {
}


Transform::~Transform() {
}


bool Transform::IsTouching(const Transform& other) const {
	float distance = (m_position - other.Position()).length();
	return (distance <= m_radius + other.Radius());
}
