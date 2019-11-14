#include "MainGame.h"
#include "Errors.h"

#include <iostream>
#include <string>


MainGame::MainGame(int width, int height) :
	m_pWindow(nullptr),
	m_screenWidth(width),
	m_screenHeight(height),
	m_gameState(GameState::PLAY),
	m_time(0),
	m_maxFPS(60) {
}


MainGame::~MainGame() {
}


void MainGame::Run() {
	InitSystems();

	testSprites.push_back(new Sprite());
	testSprites.push_back(new Sprite());
	testSprites[0]->Init(-1, -1, 1, 1, "Textures/Pixel Adventure 1/Main Characters/Ninja Frog/Jump (32x32).png");
	testSprites[1]->Init(0, 0, 1, 1, "Textures/Pixel Adventure 1/Main Characters/Ninja Frog/Jump (32x32).png");

	for (int i = 0; i < 10; ++i) {
		testSprites.push_back(new Sprite());
		testSprites.back()->Init(0, 0, 1, 1, "Textures/Pixel Adventure 1/Main Characters/Ninja Frog/Jump (32x32).png");
	}

	GameLoop();
}


void MainGame::InitSystems() {

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//	SDL_GL_SetSwapInterval(1);		// VSYNC
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

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	std::printf("**  OpenGL Version : %s  **\n", glGetString(GL_VERSION));

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

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				m_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				//std::cout << event.motion.x << " " << event.motion.y << std::endl;
				break;
		}
	}

}


void MainGame::DrawGame() {

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_colorProgram.Use();


	glActiveTexture(GL_TEXTURE0);
	GLint timeLocation = m_colorProgram.GetUniformLocation("time");
	glUniform1f(timeLocation, m_time);
	GLint textureLocation = m_colorProgram.GetUniformLocation("shaderTexture");
	glUniform1i(textureLocation, 0);

	for (int i = 0; i < testSprites.size(); ++i) {
		testSprites[i]->Draw();
	}


	m_colorProgram.Unuse();
	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_GL_SwapWindow(m_pWindow);
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