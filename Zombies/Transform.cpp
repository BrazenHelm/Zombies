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


void Transform2D::Update() {
	m_position += Velocity();
}


float Transform2D::DistanceTo(const Transform2D& other) const {
	return glm::length(m_position - other.Position());
}


bool Transform2D::IsTouching(const Transform2D& other) const {
	if (m_colliderType == ColliderType::BOX) {
		if (other.Collider() == ColliderType::BOX) {
			float xDistance = std::abs(m_position.x - other.Position().x);
			float yDistance = std::abs(m_position.y - other.Position().y);
			float distance = (xDistance > yDistance) ? xDistance : yDistance;
			return (distance < (m_radius + other.Radius()));
		}
		if (other.Collider() == ColliderType::CIRCLE) {
			int right = (m_position.x > other.Position().x) ? 1 : -1;
			int above = (m_position.y > other.Position().y) ? 1 : -1;
			glm::vec2 nearestCorner = glm::vec2(
				m_position.x + right * m_radius,
				m_position.y + above * m_radius
			);
			float distance = glm::length(other.Position() - nearestCorner);
			return (distance < other.Radius());
		}
	}
	if (m_colliderType == ColliderType::CIRCLE) {
		if (other.Collider() == ColliderType::BOX) {
			int right = (m_position.x > other.Position().x) ? 1 : -1;
			int above = (m_position.y > other.Position().y) ? 1 : -1;
			glm::vec2 nearestCorner = glm::vec2(
				other.Position().x - right * other.Radius(),
				other.Position().y - above * other.Radius()
			);
			float distance = glm::length(m_position - nearestCorner);
			return (distance < m_radius);
		}
		if (other.Collider() == ColliderType::CIRCLE) {
			return (DistanceTo(other) < m_radius + other.Radius());
		}
	}
	return false;
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