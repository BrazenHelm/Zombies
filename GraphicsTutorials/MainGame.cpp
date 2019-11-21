#include "MainGame.h"

#include <MyGameEngine/Errors.h>
#include <MyGameEngine/MyGameEngine.h>

#include <iostream>
#include <string>

using namespace MyGameEngine;

MainGame::MainGame(int width, int height) :
	m_screenWidth(width),
	m_screenHeight(height),
	m_gameState(GameState::PLAY),
	m_time(0),
	m_maxFPS(60) {
	m_camera.Init(width, height);
}


MainGame::~MainGame() {
}


void MainGame::Run() {
	InitSystems();

	testSprites.push_back(new Sprite());
	testSprites.push_back(new Sprite());
	testSprites[0]->Init(0, 0, m_screenWidth/2, m_screenWidth / 2, "Textures/Pixel Adventure 1/Main Characters/Ninja Frog/Jump (32x32).png");
	testSprites[1]->Init(m_screenWidth / 2, 0, m_screenWidth / 2, m_screenWidth / 2, "Textures/Pixel Adventure 1/Main Characters/Ninja Frog/Jump (32x32).png");

	//for (int i = 0; i < 10; ++i) {
	//	testSprites.push_back(new Sprite());
	//	testSprites.back()->Init(0, 0, 1, 1, "Textures/Pixel Adventure 1/Main Characters/Ninja Frog/Jump (32x32).png");
	//}

	GameLoop();
}


void MainGame::InitSystems() {

	MyGameEngine::Init();

	m_window.Create("Game Engine", m_screenWidth, m_screenHeight, 0);

	InitShaders();
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

		float startTicks = SDL_GetTicks();

		ProcessInput();

		m_camera.Update();

		DrawGame();
		m_time += 0.01f;
		CalculateFPS();

		static int frameCounter = 0;
		if (frameCounter++ == 20) {
			std::cout << "FPS: " << m_FPS << std::endl;
			frameCounter = 0;
		}

		float frameTicks = SDL_GetTicks() - startTicks;
		
		if (1000 / m_maxFPS > frameTicks) {
			SDL_Delay(1000 / m_maxFPS - frameTicks);
		}
	}
}


void MainGame::ProcessInput() {

	SDL_Event event;
	const float CAMERA_SPEED = 10;
	const float SCALE_SPEED = 0.1;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				m_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				//std::cout << event.motion.x << " " << event.motion.y << std::endl;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_w:
						m_camera.SetPosition(m_camera.Position() + glm::vec2(0, CAMERA_SPEED));
						break;
					case SDLK_a:
						m_camera.SetPosition(m_camera.Position() + glm::vec2(-CAMERA_SPEED,0));
						break;
					case SDLK_s:
						m_camera.SetPosition(m_camera.Position() + glm::vec2(0, -CAMERA_SPEED));
						break;
					case SDLK_d:
						m_camera.SetPosition(m_camera.Position() + glm::vec2(CAMERA_SPEED,0));
						break;
					case SDLK_q:
						m_camera.SetScale(m_camera.Scale() + SCALE_SPEED);
						break;
					case SDLK_e:
						m_camera.SetScale(m_camera.Scale() - SCALE_SPEED);
						break;
				}
				break;
		}
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
	GLint timeLocation = m_colorProgram.GetUniformLocation("time");
	glUniform1f(timeLocation, m_time);
	GLint textureLocation = m_colorProgram.GetUniformLocation("shaderTexture");
	glUniform1i(textureLocation, 0);

	for (int i = 0; i < testSprites.size(); ++i) {
		testSprites[i]->Draw();
	}


	m_colorProgram.Unuse();
	glBindTexture(GL_TEXTURE_2D, 0);
	m_window.Swap();
}


void MainGame::CalculateFPS() {
	static const int N_SAMPLES = 100;
	static float frameTimes[N_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();
	float currentTicks = SDL_GetTicks();
	m_frameTime = currentTicks - prevTicks;
	prevTicks = currentTicks;
	frameTimes[currentFrame % N_SAMPLES] = m_frameTime;

	currentFrame++;
	int count = (currentFrame < N_SAMPLES) ? currentFrame : N_SAMPLES;

	float meanFrameTime = 0;
	for (int i = 0; i < count; ++i) {
		meanFrameTime += frameTimes[i];
	}
	meanFrameTime /= count;

	if (meanFrameTime == 0) {
		m_FPS = 0;
	}
	else {
		m_FPS = 1000 / meanFrameTime;
	}
}