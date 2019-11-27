#pragma once

#include <memory>

#include <MyGameEngine/Camera2D.h>
#include <MyGameEngine/InputManager.h>
#include <MyGameEngine/GLSLProgram.h>
#include <MyGameEngine/SpriteBatch.h>
#include <MyGameEngine/Window.h>

#include "Actor.h"

class Game
{
public:
	Game();
	~Game();

	// Start the game
	void Run();

private:
	// Initialise core systems
	void InitSystems();
	
	// Initilaise shaders
	void InitShaders();

	// Main game loop for the program, runs each frame
	void GameLoop();

	// Handle input processing
	void ProcessInput();

	// Render the game
	void DrawGame();

	// Set up the initial actors
	void CreateActors();

	// Update the actors
	void UpdateActors();

	MyGameEngine::Camera2D		m_mainCamera;
	MyGameEngine::GLSLProgram	m_shaderProgram;
	MyGameEngine::InputManager	m_inputManager;
	MyGameEngine::SpriteBatch	m_spriteBatch;
	MyGameEngine::Window		m_gameWindow;

	std::vector<Actor*>	m_pActors;
};

