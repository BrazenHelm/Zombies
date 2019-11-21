#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace MyGameEngine {

class Camera2D
{
private:
	int m_screenWidth, m_screenHeight;

	float		m_scale;
	glm::vec2	m_position;
	glm::mat4	m_cameraMatrix;
	glm::mat4	m_orthoMatrix;

	bool m_needsMatrixUpdate;

public:
	Camera2D();
	~Camera2D();
	
	void Init(int screenWidth, int screenHeight);
	void Update();

	void SetScale(float newScale) {
		m_scale = newScale;
		m_needsMatrixUpdate = true;
	}
	void SetPosition(glm::vec2 newPosition) {
		m_position = newPosition;
		m_needsMatrixUpdate = true;
	}

	const float Scale()				{ return m_scale; }
	const glm::vec2 Position()		{ return m_position; }
	const glm::mat4 CameraMatrix()	{ return m_cameraMatrix; }
};

}
