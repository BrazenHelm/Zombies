#include "Game.h"

#include <MyGameEngine/MyGameEngine.h>
#include <MyGameEngine/GLTexture.h>
#include <MyGameEngine/ResourceManager.h>
#include <MyGameEngine/Time.h>

#include <SDL/SDL.h>

#include <iostream>

#include "Human.h"
#include "Zombie.h"


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
	m_spriteBatch.Init();

	CreateActors();	
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
	fpsLimiter.Init(20);

	while (true) {
		fpsLimiter.BeginFrame();

		m_mainCamera.Update();
		UpdateActors();
		ProcessInput();
		DrawGame();

		fpsLimiter.EndFrame();
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

	static bool clicked = false;
	if (m_inputManager.IsKeyPressed(SDL_BUTTON_LEFT) && !clicked) {
		std::cout << "making a zombie" << std::endl;
		glm::vec2 mousePos = m_mainCamera.ScreenToWorldPosition(m_inputManager.MousePosition());
		m_pActors.push_back(new Zombie(mousePos));
		clicked = true;
	}
	if (!m_inputManager.IsKeyPressed(SDL_BUTTON_LEFT)) {
		clicked = false;
	}
}


void Game::DrawGame() {

	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shaderProgram.Use();

	glActiveTexture(GL_TEXTURE0);
	GLint pLocation = m_shaderProgram.GetUniformLocation("P");
	glm::mat4 cameraMatrix = m_mainCamera.CameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	GLint textureLocation = m_shaderProgram.GetUniformLocation("shaderTexture");
	glUniform1i(textureLocation, 0);

	m_spriteBatch.Begin();

	for (auto pActor : m_pActors) {
		pActor->Draw(m_spriteBatch);
	}

	m_spriteBatch.End();
	m_spriteBatch.Render();

	m_shaderProgram.Unuse();
	glBindTexture(GL_TEXTURE_2D, 0);
	m_gameWindow.Swap();
}


void Game::CreateActors() {

	for (int i = -3; i <= 3; ++i) {
		glm::vec2 pos = glm::vec2(i * 100, 0);
		m_pActors.push_back(new Human(pos));
	}
}


void Game::UpdateActors() {

	for (auto& pActor : m_pActors) {

		float minDist = 0;
		Actor* nearestEnemy = new Human();
		bool foundEnemy = false;

		for (auto pOtherActor : m_pActors) {

			if (pOtherActor->Type() == pActor->Type()) continue;

			float distance = pActor->transform().DistanceTo(pOtherActor->transform());
			if (!foundEnemy || distance < minDist) {
				*nearestEnemy = *pOtherActor;
				minDist = distance;
				foundEnemy = true;
			}
		}

		if (foundEnemy) {
			pActor->Update(*nearestEnemy);
			pActor->transform().Update();
		}

		delete nearestEnemy;
	}
}