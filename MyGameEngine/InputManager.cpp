#include "InputManager.h"

namespace MyGameEngine {

InputManager::InputManager() :
	m_mousePos{ 0.0f, 0.0f } {
}


InputManager::~InputManager() {
}


void InputManager::PressKey(unsigned int keyID) {
	m_keyMap[keyID] = true;
}


void InputManager::ReleaseKey(unsigned int keyID) {
	m_keyMap[keyID] = false;
}


void InputManager::SetMousePosition(float x, float y) {
	m_mousePos.x = x;
	m_mousePos.y = y;
}


bool InputManager::IsKeyPressed(unsigned int keyID) {
	auto it = m_keyMap.find(keyID);
	if (it != m_keyMap.end()) {
		return it->second;
	}
	else {
		return false;
	}
}

}