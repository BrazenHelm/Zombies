#pragma once

#include "GLSLProgram.h"
#include "Sprite.h"

#include <SDL/SDL.h>
#include <GL/glew.h>

enum class GameState {PLAY, EXIT};

class MainGame {
private:
	SDL_Window* m_pWindow;
	int m_screenWidth;
	int m_screenHeight;

	GameState m_gameState;
	float m_time;

	Sprite testSprite;

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

};
