#pragma once

#include <glm/glm.hpp>

#include <unordered_map>

namespace MyGameEngine {

class InputManager
{
private:
	std::unordered_map<unsigned int, bool> m_keyMap;
	glm::vec2 m_mousePos;

public:
	InputManager();
	~InputManager();

	void PressKey(unsigned int keyID);
	void ReleaseKey(unsigned int keyID);
	void SetMousePosition(float x, float y);

	bool IsKeyPressed(unsigned int keyID);
	glm::vec2 MousePosition() const { return m_mousePos; }
};

}
