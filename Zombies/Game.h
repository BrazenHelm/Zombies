#pragma once

#include <memory>

#include <MyGameEngine/Audio.h>
#include <MyGameEngine/Camera2D.h>
#include <MyGameEngine/InputManager.h>
#include <MyGameEngine/GLSLProgram.h>
#include <MyGameEngine/SpriteBatch.h>
#include <MyGameEngine/SpriteFont.h>
#include <MyGameEngine/Window.h>
#include <MyGameEngine/ParticleSystem2D.h>

#include "Level.h"
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"

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

	// Play the game music in an infinite loop
	void PlayMusic();
	
	// Initilaise shaders
	void InitShaders();

	// Main game loop for the program, runs each frame
	void GameLoop();

	// Handle input processing
	void ProcessInput();

	// Update the actors
	void UpdateActors(float deltaTime);

	// Update the camera to follow the player
	void UpdateCamera();

	// Blood splatter
	void AddBlood(const glm::vec2& pos, int n_particles);

	// Render the game
	void DrawGame();
	void DrawActors();
	void DrawHUD();


	MyGameEngine::Audio::AudioSource m_audioSource;

	MyGameEngine::Camera2D			m_mainCamera;
	MyGameEngine::Camera2D			m_uiCamera;
	MyGameEngine::GLSLProgram		m_shaderProgram;
	MyGameEngine::InputManager		m_inputManager;
	MyGameEngine::ParticleSystem2D	m_particleSystem;
	MyGameEngine::ParticleBatch2D*	m_pBloodParticleBatch;
	MyGameEngine::SpriteBatch		m_spriteBatch;
	MyGameEngine::SpriteFont*		m_pSpriteFont;
	MyGameEngine::SpriteBatch		m_uiSpriteBatch;
	MyGameEngine::Window			m_gameWindow;

	std::vector<Level*>			m_pLevels;			// data for all the levels in the game

	// current level variables
	std::vector<Actor*>	 m_pHumans;			// all humans in the level; 0th element is m_pPlayer
	std::vector<Actor*>	 m_pZombies;			// all zombies in the level
	Player*				 m_pPlayer = nullptr;	// the player; equivalent to m_pHumans[0]
	std::vector<Bullet>	 m_bullets;

	// game state variables
	GameState m_gameState = GameState::PLAY;
	int m_currentLevel = 0;

	Level* CurrentLevel() { return m_pLevels[m_currentLevel]; }

	// scoring variables
	int m_nZombiesKilled = 0;
	int m_nCivsKilled = 0;
};

