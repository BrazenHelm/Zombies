#pragma once

#include <MyGameEngine/Camera2D.h>
#include <MyGameEngine/GLSLProgram.h>
#include <MyGameEngine/GLTexture.h>
#include <MyGameEngine/InputManager.h>
#include <MyGameEngine/Sprite.h>
#include <MyGameEngine/SpriteBatch.h>
#include <MyGameEngine/Time.h>
#include <MyGameEngine/Window.h>

#include <SDL/SDL.h>
#include <GL/glew.h>

using namespace MyGameEngine;

enum class GameState {PLAY, EXIT};

class MainGame {
private:
	Window		m_window;
	int			m_screenWidth;
	int			m_screenHeight;
	Camera2D	m_camera;

	GameState	m_gameState;

	SpriteBatch testSpriteBatch;

	GLSLProgram		m_colorProgram;
	InputManager	m_inputManager;
	FPSLimiter		m_fpsLimiter;

public:
	MainGame(int width, int height);
	~MainGame();

	void Run();

private:
	void InitSystems();
	void InitShaders();
	void GameLoop();
	void ProcessInput();
	void DrawGame();
};
