#pragma once

#include <unordered_map>

namespace MyGameEngine {

class InputManager
{
private:
	std::unordered_map<unsigned int, bool> m_keyMap;

public:
	InputManager();
	~InputManager();

	void PressKey(unsigned int keyID);
	void ReleaseKey(unsigned int keyID);
	bool IsKeyPressed(unsigned int keyID);
};

}
