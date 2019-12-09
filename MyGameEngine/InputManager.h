#pragma once

#include <glm/glm.hpp>

#include <unordered_map>

namespace MyGameEngine {

class InputManager
{
private:
	std::unordered_map<unsigned int, bool> m_keyMap;
	std::unordered_map<unsigned int, bool> m_prevKeyMap;
	glm::vec2 m_mousePos;

public:
	InputManager();
	~InputManager();

	void PressKey(unsigned int keyID);
	void ReleaseKey(unsigned int keyID);
	void SetMousePosition(int x, int y);

	// Should be called every frame
	void Update();

	// Returns true if the key is currently held down
	bool KeyHeld(unsigned int keyID);

	// Returns true on the frame that the key is pressed
	bool KeyDown(unsigned int keyID);

	// Returns true on the frame that the key is released
	bool KeyUp(unsigned int keyID);

	glm::vec2 MousePosition() const { return m_mousePos; }

private:
	bool KeyWasHeld(unsigned int keyID);
};

}
