#include "Camera2D.h"

namespace MyGameEngine {

Camera2D::Camera2D() :
	m_screenWidth(0), m_screenHeight(0),
	m_scale(1.0f), m_position(0, 0),
	m_needsMatrixUpdate(true) {
}


Camera2D::~Camera2D() {
}


void Camera2D::Init(int screenWidth, int screenHeight) {
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
}


void Camera2D::Update() {

	if (m_needsMatrixUpdate) {

		glm::vec3 translation{ m_screenWidth / 2 - m_position.x, m_screenHeight / 2 - m_position.y, 0 };
		m_cameraMatrix = glm::translate(m_orthoMatrix, translation);

		glm::vec3 scaling{ m_scale, m_scale, 0 };
		m_cameraMatrix = glm::scale(m_cameraMatrix, scaling);

		m_needsMatrixUpdate = false;
	}
}


glm::vec2 Camera2D::ScreenToWorldPosition(glm::vec2 screenPosition) {
	screenPosition -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);		// centre on (0,0)
	screenPosition.y *= -1;													// invert y-axis
	screenPosition += m_position;											// translate
	screenPosition /= m_scale;												// scale
	return screenPosition;
}


}
