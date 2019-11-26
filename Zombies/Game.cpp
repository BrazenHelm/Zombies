#include "Game.h"

#include <MyGameEngine/MyGameEngine.h>

#include <SDL/SDL.h>


Game::Game() {
	// Empty
}


Game::~Game() {
	// Empty
}


void Game::Run() {
	InitSystems();
	GameLoop();
}


void Game::InitSystems() {

	MyGameEngine::Init();

	const int WIDTH = 800;
	const int HEIGHT = 600;

	m_mainCamera.Init(WIDTH, HEIGHT);
	m_gameWindow.Create("Zombies", WIDTH, HEIGHT, 0);
	InitShaders();
}


void Game::InitShaders() {
	// Compile the color shader
	m_shaderProgram.CompileShaders("Shaders/vertexShader", "Shaders/fragmentShader");
	m_shaderProgram.AddAttribute("vertexPosition");
	m_shaderProgram.AddAttribute("vertexColor");
	m_shaderProgram.AddAttribute("vertexUV");
	m_shaderProgram.LinkShaders();
}


void Game::GameLoop() {

	while (true) {

		for (Actor* actor : m_actors) {
			actor->Update();
		}

		m_mainCamera.Update();

		ProcessInput();
		DrawGame();

	}

}


void Game::ProcessInput() {
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
			case SDL_QUIT:
				// quit game
				break;
			case SDL_MOUSEMOTION:
				m_inputManager.SetMousePosition(evnt.motion.x, evnt.motion.y);
				break;
			case SDL_KEYDOWN:
				m_inputManager.PressKey(evnt.key.keysym.sym);
				break;
			case SDL_KEYUP:
				m_inputManager.ReleaseKey(evnt.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_inputManager.PressKey(evnt.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				m_inputManager.ReleaseKey(evnt.button.button);
				break;
		}
	}
}


void Game::DrawGame() {

	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shaderProgram.Use();




	m_shaderProgram.Unuse();

	m_gameWindow.Swap();
}