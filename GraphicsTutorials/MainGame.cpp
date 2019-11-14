#include "MainGame.h"
#include "Errors.h"

#include <iostream>
#include <string>

#include "ImageLoader.h"

MainGame::MainGame(int width, int height) :
	m_pWindow(nullptr),
	m_screenWidth(width),
	m_screenHeight(height),
	m_gameState(GameState::PLAY),
	m_time(0) {
}


MainGame::~MainGame() {
}


void MainGame::Run() {
	InitSystems();

	playerTexture = ImageLoader::LoadPNG("Textures/Pixel Adventure 1/Main Characters/Ninja Frog/Jump (32x32).png");
	testSprite.Init(-0.5, -0.5, 1, 1);

	GameLoop();
}


void MainGame::InitSystems() {

	SDL_Init(SDL_INIT_EVERYTHING);

	m_pWindow = SDL_CreateWindow("GameEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth, m_screenHeight, SDL_WINDOW_OPENGL);
	if (m_pWindow == nullptr) {
		FatalError("SDL Window could not be created.");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(m_pWindow);
	if (glContext == nullptr) {
		FatalError("SDL_GL Context could not be created.");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		FatalError("GLEW could not be initialised.");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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
		ProcessInput();
		DrawGame();
		m_time += 0.001;
	}
}


void MainGame::ProcessInput() {

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				m_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				std::cout << event.motion.x << " " << event.motion.y << std::endl;
				break;
		}
	}

}


void MainGame::DrawGame() {

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, playerTexture.id);
	m_colorProgram.Use();


	glActiveTexture(GL_TEXTURE0);
	GLint timeLocation = m_colorProgram.GetUniformLocation("time");
	glUniform1f(timeLocation, m_time);
	GLint textureLocation = m_colorProgram.GetUniformLocation("shaderTexture");
	glUniform1i(textureLocation, 0);

	testSprite.Draw();


	m_colorProgram.Unuse();
	glBindTexture(GL_TEXTURE_2D, playerTexture.id);
	SDL_GL_SwapWindow(m_pWindow);
}
