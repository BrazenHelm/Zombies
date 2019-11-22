#include "MainGame.h"

#include <MyGameEngine/Errors.h>
#include <MyGameEngine/MyGameEngine.h>
#include <MyGameEngine/ResourceManager.h>
#include <MyGameEngine/Time.h>

#include <iostream>
#include <string>

using namespace MyGameEngine;

MainGame::MainGame(int width, int height) :
	m_screenWidth (width),
	m_screenHeight (height),
	m_gameState	(GameState::PLAY) {
	m_camera.Init(width, height);
}


MainGame::~MainGame() {
}


void MainGame::Run() {
	InitSystems();
	GameLoop();
}


void MainGame::InitSystems() {
	MyGameEngine::Init();
	m_window.Create("Game Engine", m_screenWidth, m_screenHeight, 0);
	InitShaders();
	testSpriteBatch.Init();
	m_fpsLimiter.Init();
}


void MainGame::InitShaders() {
	m_colorProgram.CompileShaders("Shaders/vertexShader.txt", "Shaders/fragmentShader.txt");
	m_colorProgram.AddAttribute("vertexPosition");
	m_colorProgram.AddAttribute("vertexColor");
	m_colorProgram.AddAttribute("vertexUV");
	m_colorProgram.LinkShaders();
}


void MainGame::GameLoop() {

	while (m_gameState != GameState::EXIT) {

		m_fpsLimiter.BeginFrame();

		ProcessInput();
		m_camera.Update();
		DrawGame();

		static int frameCounter = 0;
		if (frameCounter++ == 2000) {
			std::cout << "FPS: " << m_fpsLimiter.GetFPS() << std::endl;
			frameCounter = 0;
		}
		m_fpsLimiter.EndFrame();
	}
}


void MainGame::ProcessInput() {

	SDL_Event ev;
	const float CAMERA_SPEED = 3;
	const float SCALE_SPEED = 0.1;

	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
			case SDL_QUIT:
				m_gameState = GameState::EXIT;
				break;
			case SDL_KEYDOWN:
				m_inputManager.PressKey(ev.key.keysym.sym);
				break;
			case SDL_KEYUP:
				m_inputManager.ReleaseKey(ev.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_inputManager.PressKey(ev.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				m_inputManager.ReleaseKey(ev.button.button);
				break;
			case SDL_MOUSEMOTION:
				m_inputManager.SetMousePosition(ev.motion.x, ev.motion.y);
				break;
		}
	}

	if (m_inputManager.IsKeyPressed(SDLK_w)) {
		m_camera.SetPosition(m_camera.Position() + glm::vec2(0, CAMERA_SPEED));
	}
	if (m_inputManager.IsKeyPressed(SDLK_a)) {
		m_camera.SetPosition(m_camera.Position() + glm::vec2(-CAMERA_SPEED, 0));
	}
	if (m_inputManager.IsKeyPressed(SDLK_s)) {
		m_camera.SetPosition(m_camera.Position() + glm::vec2(0, -CAMERA_SPEED));
	}
	if (m_inputManager.IsKeyPressed(SDLK_d)) {
		m_camera.SetPosition(m_camera.Position() + glm::vec2(CAMERA_SPEED, 0));
	}
	if (m_inputManager.IsKeyPressed(SDLK_q)) {
		m_camera.SetScale(m_camera.Scale() + SCALE_SPEED);
	}
	if (m_inputManager.IsKeyPressed(SDLK_e)) {
		m_camera.SetScale(m_camera.Scale() - SCALE_SPEED);
	}
	if (m_inputManager.IsKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mousePos = m_camera.ScreenToWorldPosition(m_inputManager.MousePosition());
		std::cout << mousePos.x << " " << mousePos.y << std::endl;
	}
}


void MainGame::DrawGame() {

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_colorProgram.Use();


	glActiveTexture(GL_TEXTURE0);
	GLint pLocation = m_colorProgram.GetUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.CameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	//GLint timeLocation = m_colorProgram.GetUniformLocation("time");
	//glUniform1f(timeLocation, m_time);
	GLint textureLocation = m_colorProgram.GetUniformLocation("shaderTexture");
	glUniform1i(textureLocation, 0);

	testSpriteBatch.Begin();

	glm::vec4 pos1{ 0, 0, 50, 50 };
	glm::vec4 pos2{ 100, 50, 50, 50 };
	glm::vec4 uv{ 0, 0, 1, 1 };
	static GLTexture texture1 = ResourceManager::GetTexture("Textures/Pixel Adventure 1/Items/Boxes/Box1/Idle.png");
	static GLTexture texture2 = ResourceManager::GetTexture("Textures/Pixel Adventure 1/Main Characters/Ninja Frog/Jump (32x32).png");
	Color color;
	color.r = 255; color.g = 255; color.b = 255; color.a = 255;

	testSpriteBatch.Draw(pos1, uv, texture1.id, 0, color);
	testSpriteBatch.Draw(pos2, uv, texture2.id, 0, color);

	testSpriteBatch.End();
	testSpriteBatch.Render();

	m_colorProgram.Unuse();
	glBindTexture(GL_TEXTURE_2D, 0);
	m_window.Swap();
}

