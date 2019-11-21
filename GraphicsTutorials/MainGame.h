#pragma once

#include <MyGameEngine/Camera2D.h>
#include <MyGameEngine/GLSLProgram.h>
#include <MyGameEngine/GLTexture.h>
#include <MyGameEngine/Sprite.h>
#include <MyGameEngine/Window.h>

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <vector>

using namespace MyGameEngine;

enum class GameState {PLAY, EXIT};

class MainGame {
private:
	Window		m_window;
	int			m_screenWidth;
	int			m_screenHeight;
	Camera2D	m_camera;

	GameState m_gameState;

	float m_time;
	float m_frameTime;
	float m_FPS;
	float m_maxFPS;

	std::vector<Sprite*> testSprites;

	GLSLProgram m_colorProgram;

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
	void CalculateFPS();
};
