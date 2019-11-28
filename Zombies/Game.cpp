#include "Game.h"

#include <MyGameEngine/MyGameEngine.h>
#include <MyGameEngine/GLTexture.h>
#include <MyGameEngine/ResourceManager.h>
#include <MyGameEngine/Time.h>

#include <SDL/SDL.h>

#include <iostream>

#include "Human.h"
#include "Zombie.h"


Game::Game() :
	m_gameState(GameState::PLAY),
	m_currentLevel(0),
	m_pPlayer(nullptr) {
}


Game::~Game() {
	for (Level* level : m_pLevels) { delete level; }
	for (Human* human : m_pHumans) { delete human; }
	for (Zombie* zombie : m_pZombies) { delete zombie; }
	delete m_pPlayer;
}


void Game::Run() {
	InitSystems();
	LoadLevels();
	GameLoop();
}


void Game::InitSystems() {

	MyGameEngine::Init();

	const int WIDTH = 800;
	const int HEIGHT = 600;

	m_gameWindow.Create("Zombies", WIDTH, HEIGHT, 0);
	m_mainCamera.Init(WIDTH, HEIGHT);
	InitShaders();
	m_spriteBatch.Init();
}


void Game::LoadLevels() {
	m_pLevels.push_back(new Level("Level Data/Level 1.txt"));
	SetUpLevel(m_currentLevel);
}


void Game::SetUpLevel(int levelIndex) {
	// Create player
	glm::vec2 playerStartPos = m_pLevels[m_currentLevel]->PlayerStart();
	m_pPlayer = new Player(playerStartPos, &m_inputManager);
	m_pHumans.push_back(m_pPlayer);
}


void Game::InitShaders() {
	// Compile the color shader
	m_shaderProgram.CompileShaders("Shaders/vertexShader.txt", "Shaders/fragmentShader.txt");
	m_shaderProgram.AddAttribute("vertexPosition");
	m_shaderProgram.AddAttribute("vertexColor");
	m_shaderProgram.AddAttribute("vertexUV");
	m_shaderProgram.LinkShaders();
}


void Game::GameLoop() {

	MyGameEngine::FPSLimiter fpsLimiter;
	fpsLimiter.Init();

	while (m_gameState != GameState::EXIT) {
		fpsLimiter.BeginFrame();

		ProcessInput();
		UpdateActors();
		UpdateCamera();
		DrawGame();

		fpsLimiter.EndFrame();
	}

}


void Game::ProcessInput() {
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
			case SDL_QUIT:
				m_gameState = GameState::EXIT;
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

	/*static bool clicked = false;
	if (m_inputManager.IsKeyPressed(SDL_BUTTON_LEFT) && !clicked) {
		std::cout << "making a zombie" << std::endl;
		glm::vec2 mousePos = m_mainCamera.ScreenToWorldPosition(m_inputManager.MousePosition());
		m_pZombies.push_back(new Zombie(mousePos));
		clicked = true;
	}
	if (!m_inputManager.IsKeyPressed(SDL_BUTTON_LEFT)) {
		clicked = false;
	}*/
}


void Game::UpdateActors() {
	for (auto pHuman : m_pHumans)	{ pHuman->Update(); }
	for (auto pZombie : m_pZombies) { pZombie->Update(); }
}


void Game::UpdateCamera() {
	m_mainCamera.SetPosition(m_pPlayer->Transform().Position());
	m_mainCamera.Update();
}


void Game::DrawGame() {

	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	m_shaderProgram.Use();

	GLint pLocation = m_shaderProgram.GetUniformLocation("P");
	glm::mat4 cameraMatrix = m_mainCamera.CameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLint textureLocation = m_shaderProgram.GetUniformLocation("shaderTexture");
	glUniform1i(textureLocation, 0);

	// Render the level
	m_pLevels[m_currentLevel]->Render();

	// Draw the humans and zombies. Note: player is a human
	m_spriteBatch.Begin();
	for (Human* pHuman : m_pHumans) { pHuman->Draw(m_spriteBatch); }
	for (Zombie* pZombie : m_pZombies) { pZombie->Draw(m_spriteBatch); }
	m_spriteBatch.End();

	// Render the humans and zombies
	m_spriteBatch.Render();

	m_shaderProgram.Unuse();
	glBindTexture(GL_TEXTURE_2D, 0);
	m_gameWindow.Swap();
}




