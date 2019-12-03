#include "InputManager.h"

namespace MyGameEngine {

InputManager::InputManager() :
	m_mousePos{ 0.0f, 0.0f } {
}


InputManager::~InputManager() {
}


void InputManager::Update() {
	for (auto& kvp : m_keyMap) {
		m_prevKeyMap[kvp.first] = kvp.second;
	}
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


bool InputManager::KeyHeld(unsigned int keyID) {
	auto it = m_keyMap.find(keyID);
	if (it != m_keyMap.end())
		return it->second;
	else
		return false;
}

bool InputManager::KeyDown(unsigned int keyID) {
	if (!KeyHeld(keyID)) return false;
	else if (KeyWasHeld(keyID)) return false;
	else return true;
}


bool InputManager::KeyUp(unsigned int keyID) {
	if (KeyHeld(keyID)) return false;
	else if (!KeyWasHeld(keyID)) return false;
	else return true;
}


bool InputManager::KeyWasHeld(unsigned int keyID) {
	auto it = m_prevKeyMap.find(keyID);
	if (it != m_prevKeyMap.end())
		return it->second;
	else
		return false;
}


}