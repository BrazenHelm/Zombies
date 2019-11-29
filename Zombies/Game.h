#pragma once

#include <memory>

#include <MyGameEngine/Camera2D.h>
#include <MyGameEngine/InputManager.h>
#include <MyGameEngine/GLSLProgram.h>
#include <MyGameEngine/SpriteBatch.h>
#include <MyGameEngine/Window.h>

#include "Level.h"
#include "Player.h"
#include "Zombie.h"

enum class GameState { EXIT, PLAY };

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

	// Load the levels
	void LoadLevels();

	// Set up the current level
	void SetUpLevel(int levelIndex);
	
	// Initilaise shaders
	void InitShaders();

	// Main game loop for the program, runs each frame
	void GameLoop();

	// Handle input processing
	void ProcessInput();

	// Update the actors
	void UpdateActors();

	// Update the camera to follow the player
	void UpdateCamera();

	// Render the game
	void DrawGame();




	MyGameEngine::Camera2D		m_mainCamera;
	MyGameEngine::GLSLProgram	m_shaderProgram;
	MyGameEngine::InputManager	m_inputManager;
	MyGameEngine::SpriteBatch	m_spriteBatch;
	MyGameEngine::Window		m_gameWindow;

	std::vector<Level*>			m_pLevels;			// data for all the levels in the game

	// current level variables
	std::vector<Actor*>			m_pHumans;	// all humans in the level; 0th element is m_pPlayer
	std::vector<Actor*>		m_pZombies;	// all zombies in the level
	Player*						m_pPlayer;	// the player; equivalent to m_pHumans[0]

	// game state variables
	GameState m_gameState;
	int m_currentLevel;
};

