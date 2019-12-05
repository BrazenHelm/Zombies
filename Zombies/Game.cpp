#include "Game.h"

#include <MyGameEngine/MyGameEngine.h>
#include <MyGameEngine/GLTexture.h>
#include <MyGameEngine/ResourceManager.h>
#include <MyGameEngine/Time.h>
#include <MyGameEngine/ParticleBatch2D.h>

#include <glm/gtx/rotate_vector.hpp>
#include <SDL/SDL.h>

#include <ctime>
#include <iostream>
#include <random>

#include "Human.h"
#include "Zombie.h"


Game::Game() :
	m_gameState(GameState::PLAY),
	m_currentLevel(0),
	m_pPlayer(nullptr) {
}


Game::~Game() {
	for (Level* level : m_pLevels)		{ delete level; }
	for (Actor* human : m_pHumans)		{ delete human; }
	for (Actor* zombie : m_pZombies)	{ delete zombie; }
}


void Game::Run() {
	InitSystems();
	LoadLevels();
	PlayMusic();
	GameLoop();
	system("pause");
}


void updateBloodParticle(MyGameEngine::Particle2D& p, float deltaTime) {
	p.position += p.velocity * deltaTime;
	p.color.a = (GLubyte)(p.lifetime * 1275.0f);
	p.lifetime -= deltaTime;
}


void Game::InitSystems() {

	MyGameEngine::Init();

	const int WIDTH = 800;
	const int HEIGHT = 600;

	m_audioSource.init();
	m_gameWindow.Create("Zombies", WIDTH, HEIGHT, 0);
	m_mainCamera.Init(WIDTH, HEIGHT);
	m_uiCamera.Init(WIDTH, HEIGHT);
	InitShaders();
	m_spriteBatch.Init();
	m_uiSpriteBatch.Init();
	m_pSpriteFont = new MyGameEngine::SpriteFont("Fonts/veteran_typewriter/veteran typewriter.ttf", 32);
	m_pBloodParticleBatch = new MyGameEngine::ParticleBatch2D(
		1000, 0.2f,
		MyGameEngine::ResourceManager::GetTexture("Textures/Pixel Adventure 1/Other/Dust Particle.png"),
		[](MyGameEngine::Particle2D& p, float deltaTime) {
			p.position += p.velocity * deltaTime;
			p.color.a = (GLubyte)(p.lifetime * 1275.0f);
			p.lifetime -= deltaTime;
		}
	);
	m_particleSystem.addParticleBatch(m_pBloodParticleBatch);
}


void Game::LoadLevels() {
	m_pLevels.push_back(new Level("Level Data/Level 1.txt"));
	SetUpLevel(m_currentLevel);
}


void Game::SetUpLevel(int levelIndex) {
	// Create player
	Level* pLevel = m_pLevels[m_currentLevel];
	glm::vec2 playerStartPos = pLevel->PlayerStart();
	m_pPlayer = new Player(playerStartPos, &m_inputManager, &m_mainCamera);
	m_pHumans.push_back(m_pPlayer);

	m_pPlayer->AddGun(new Gun("Magnum", 0.42f, 1, 2.5f, 1200.0f, 50,
		m_audioSource.loadSound("Audio/shots/pistol.wav")));
	m_pPlayer->AddGun(new Gun("Shotgun", 0.75f, 10, 15.0f, 1200.0f, 15,
		m_audioSource.loadSound("Audio/shots/shotgun.wav")));
	m_pPlayer->AddGun(new Gun("MP5", 0.08f, 1, 5.0f, 1200.0f, 8,
		m_audioSource.loadSound("Audio/shots/cg1.wav")));
	
	// Create random humans
	int nHumans = pLevel->NHumans();
	std::mt19937 rng;
	rng.seed((size_t)time(nullptr));
	std::uniform_int_distribution<int> width(1, pLevel->Width() - 2);
	std::uniform_int_distribution<int> height(1, pLevel->Height() - 2);

	for (int i = 0; i < nHumans; i++) {
		glm::vec2 pos = glm::vec2(width(rng) * Level::TILE_SIZE + Level::TILE_SIZE / 2, height(rng) * Level::TILE_SIZE + Level::TILE_SIZE / 2);
		m_pHumans.push_back(new Human(pos));
	}

	// Create zombies
	const std::vector<glm::vec2>& zombieStarts = pLevel->ZombieStarts();
	for (glm::vec2 pos : zombieStarts) {
		m_pZombies.push_back(new Zombie(pos));
	}
}


void Game::InitShaders() {
	// Compile the color shader
	m_shaderProgram.CompileShaders("Shaders/vertexShader.txt", "Shaders/fragmentShader.txt");
	m_shaderProgram.AddAttribute("vertexPosition");
	m_shaderProgram.AddAttribute("vertexColor");
	m_shaderProgram.AddAttribute("vertexUV");
	m_shaderProgram.LinkShaders();
}


void Game::PlayMusic() {
	MyGameEngine::Audio::Music music = m_audioSource.loadMusic("Audio/XYZ.ogg");
	music.play(-1);
}


void Game::GameLoop() {

	float MAX_FPS = 240.0f;

	MyGameEngine::Time fpsLimiter;
	fpsLimiter.Init(MAX_FPS);

	while (m_gameState != GameState::EXIT) {
		fpsLimiter.BeginFrame();

		// if the FPS is lower than 30, the game will run slower
		// this avoids bugs due to missed collisions at very low frame rates
		float deltaTime = fpsLimiter.DeltaTime();
		static const float MAX_DELTA_TIME = 1.0f / 30.0f;
		deltaTime = std::min(deltaTime, MAX_DELTA_TIME);

		// TODO: multiple physics steps at high frame rates

		ProcessInput();

		UpdateActors(deltaTime);
		UpdateCamera();
		m_inputManager.Update();
		m_particleSystem.update(deltaTime);

		DrawGame();

		fpsLimiter.EndFrame();
		static int frameCount;
		if (frameCount++ == 60) {
			frameCount = 0;
			std::cout << "FPS: " << fpsLimiter.GetFPS() << std::endl;
		}
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

	/* Spawn a zombie at mouse click location */
	//static bool clicked = false;
	//if (m_inputManager.IsKeyPressed(SDL_BUTTON_LEFT) && !clicked) {
	//	std::cout << "making a zombie" << std::endl;
	//	glm::vec2 mousePos = m_mainCamera.ScreenToWorldPosition(m_inputManager.MousePosition());
	//	m_pZombies.push_back(new Zombie(mousePos));
	//	clicked = true;
	//}
	//if (!m_inputManager.IsKeyPressed(SDL_BUTTON_LEFT)) {
	//	clicked = false;
	//}
}


void Game::UpdateActors(float deltaTime) {
	// Update humans and zombies. Returning true means actor has died
	if (m_pPlayer->Update(m_pHumans, m_pZombies, m_bullets, deltaTime)) {
		std::printf("*** You died... ***\n");
		std::printf("Zombies killed: %d\n", m_nZombiesKilled);
		std::printf("Civilians killed: %d\n", m_nCivsKilled);
		m_gameState = GameState::EXIT;
	}
	for (size_t i = 1; i < m_pHumans.size(); i++) {
		if (m_pHumans[i]->Update(m_pHumans, m_pZombies, deltaTime)) {
			AddBlood(m_pHumans[i]->Transform().Position(), 20);
			delete m_pHumans[i];
			m_pHumans[i] = m_pHumans.back();
			m_pHumans.pop_back();
			m_nCivsKilled++;
		}
	}
	for (size_t j = 0; j < m_pZombies.size(); j++) {
		if (m_pZombies[j]->Update(m_pHumans, m_pZombies, deltaTime)) {
			AddBlood(m_pZombies[j]->Transform().Position(), 20);
			delete m_pZombies[j];
			m_pZombies[j] = m_pZombies.back();
			m_pZombies.pop_back();
			m_nZombiesKilled++;
			if (m_pZombies.size() == 0) {
				std::printf("*** All zombies defeated! ***\n");
				std::printf("Zombies killed: %d\n", m_nZombiesKilled);
				std::printf("Civilians killed: %d\n", m_nCivsKilled);
				std::printf("Civilians saved: %d/%d\n", m_pHumans.size() - 1, m_pLevels[m_currentLevel]->NHumans());
				m_gameState = GameState::EXIT;
			}
		}
	}

	// Do collision for humans and zombies with terrain
	for (auto pHuman : m_pHumans)	{ pHuman->DoLevelCollision(CurrentLevel()->LevelData()); }
	for (auto pZombie : m_pZombies) { pZombie->DoLevelCollision(CurrentLevel()->LevelData()); }

	// Do collision for humans with humans
	for (size_t i = 0; i < m_pHumans.size(); i++) {
		for (size_t j = i + 1; j < m_pHumans.size(); j++) {
			m_pHumans[i]->CollideWith(m_pHumans[j]);
		}
	}
	// Do collision for zombies with zombies
	for (size_t i = 0; i < m_pZombies.size(); i++) {
		for (size_t j = i + 1; j < m_pZombies.size(); j++) {
			m_pZombies[i]->CollideWith(m_pZombies[j]);
		}
	}
	// Do collision for zombies with player
	for (size_t i = 0; i < m_pZombies.size(); i++) {
		if (m_pPlayer->CollideWith(m_pZombies[i])) {
			m_pZombies[i]->TakeDamage(INT_MAX); // kill the zombie
			m_pPlayer->TakeDamage(Zombie::Damage());
		}
	}
	// Do collision for zombies with other humans
	for (size_t i = 0; i < m_pZombies.size(); i++) {
		for (size_t j = m_pHumans.size() - 1; j > 0; j--) {
			if (m_pZombies[i]->CollideWith(m_pHumans[j])) {
				AddBlood(m_pHumans[j]->Transform().Position(), 20);
				Zombie* newZombie = new Zombie(m_pHumans[j]->Transform().Position());
				delete m_pHumans[j];
				m_pHumans[j] = m_pHumans.back();
				m_pHumans.pop_back();
				//m_pHumans.erase(m_pHumans.begin() + j);
				m_pZombies.push_back(newZombie);
			}
		}
	}

	// Update bullets
	for (Bullet& bullet : m_bullets) { bullet.Update(deltaTime); }

	// Do collision for bullets ...
	for (size_t i = 0; i < m_bullets.size();) {

		bool foundCollision = false;

		// with terrain
		if (m_bullets[i].CollideWithWorld(CurrentLevel()->LevelData())) {
			m_bullets[i] = m_bullets.back();
			m_bullets.pop_back();
			foundCollision = true;
		}
		if (foundCollision) continue;

		// with humans (not the player)
		for (size_t j = 1; j < m_pHumans.size(); j++) {
			if (m_bullets[i].CollideWith(m_pHumans[j])) {
				AddBlood(m_bullets[i].Transform().Position(), 5);
				m_bullets[i] = m_bullets.back();
				m_bullets.pop_back();
				foundCollision = true;
				break;
			}
		}
		if (foundCollision) continue;

		// with zombies
		for (size_t k = 0; k < m_pZombies.size(); k++) {
			if (m_bullets[i].CollideWith(m_pZombies[k])) {
				AddBlood(m_bullets[i].Transform().Position(), 5);
				m_bullets[i] = m_bullets.back();
				m_bullets.pop_back();
				foundCollision = true;
				break;
			}
		}
		if (foundCollision) continue;

		i++;
	}
}


void Game::UpdateCamera() {
	m_mainCamera.SetPosition(m_pPlayer->Transform().Position());
	m_mainCamera.Update();

	m_uiCamera.Update();
}


void Game::AddBlood(const glm::vec2& pos, int n_particles) {

	glm::vec2 vel(100.0f, 0.0f);

	static std::mt19937 rng(time(nullptr));
	static std::uniform_real_distribution<float> randomAngle(0.0f, 2 * M_PI);

	MyGameEngine::Color red(200, 0, 0, 255);

	for (int i = 0; i < n_particles; i++) {
		vel = glm::rotate(vel, randomAngle(rng));
		m_pBloodParticleBatch->addParticle(pos, vel, red, 5.0f);
	}

}


void Game::DrawGame() {

	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glActiveTexture(GL_TEXTURE0);
	m_shaderProgram.Use();

	GLint pLocation = m_shaderProgram.GetUniformLocation("P");
	glm::mat4 cameraMatrix = m_mainCamera.CameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLint textureLocation = m_shaderProgram.GetUniformLocation("shaderTexture");
	glUniform1i(textureLocation, 0);

	// Render the level
	m_pLevels[m_currentLevel]->Render();

	m_spriteBatch.Begin();

	DrawActors();
	m_pBloodParticleBatch->draw(m_spriteBatch);

	m_spriteBatch.End();
	m_spriteBatch.Render();

	DrawHUD();

	m_shaderProgram.Unuse();
	m_gameWindow.Swap();
}


void Game::DrawActors() {
	for (Actor* pHuman : m_pHumans) {
		if (m_mainCamera.IsInView(pHuman->Transform().Rect()))
			pHuman->Draw(m_spriteBatch);
	}
	for (Actor* pZombie : m_pZombies) {
		if (m_mainCamera.IsInView(pZombie->Transform().Rect()))
			pZombie->Draw(m_spriteBatch);
	}
	for (Bullet bullet : m_bullets) {
		if (m_mainCamera.IsInView(bullet.Transform().Rect()))
			bullet.Draw(m_spriteBatch);
	}
}


void Game::DrawHUD() {

	GLint pLocation = m_shaderProgram.GetUniformLocation("P");
	glm::mat4 cameraMatrix = m_uiCamera.CameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_uiSpriteBatch.Begin();

	char buffer[256];

	sprintf_s(buffer, "Civilians Remaining: %d/%d",
				m_pHumans.size() - 1, CurrentLevel()->NHumans());
	m_pSpriteFont->draw(m_uiSpriteBatch, buffer, glm::vec2(395, 270),
						glm::vec2(0.8f), 0.0f, MyGameEngine::Color(255, 255, 255, 255),
						MyGameEngine::Justification::RIGHT);

	m_uiSpriteBatch.End();
	m_uiSpriteBatch.Render();
}


