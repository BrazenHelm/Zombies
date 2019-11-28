#include "Level.h"

#include <fstream>
#include <iostream>

#include <MyGameEngine/Errors.h>
#include <MyGameEngine/ResourceManager.h>


Level::Level(const std::string& filename) {

	std::ifstream file;
	file.open(filename);

	if (file.fail()) {
		MyGameEngine::FatalError("Could not load level data " + filename);
	}

	file >> m_nHumans;

	std::string buffer;
	while (std::getline(file, buffer)) {
		m_levelData.push_back(buffer);
	}

	file.close();

	//for (int i = 0; i < m_levelData.size(); ++i) {
	//	std::cout << m_levelData[i] << std::endl;
	//}
	//std::cout << "Humans: " << m_nHumans << std::endl;

	m_spriteBatch.Init();
	m_spriteBatch.Begin();

	glm::vec4 uvRect{ 0, 0, 1, 1 };
	MyGameEngine::Color white;
	white.r = 255;	white.g = 255;	white.b = 255;	white.a = 255;

	for (int y = 0; y < m_levelData.size(); y++) {
		for (int x = 0; x < m_levelData[y].size(); x++) {

			char tile = m_levelData[y][x];

			glm::vec4 rect{ x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
			GLuint wallTextureID = MyGameEngine::ResourceManager::GetTexture("Textures/wooden wall.png").id;

			switch (tile) {
				case 'w':	// wall
					m_spriteBatch.Draw(rect, uvRect, wallTextureID, 0, white);
					break;

				case '@':	// player
					m_playerStart = glm::vec2(x * TILE_SIZE, y * TILE_SIZE);
					break;

				case 'z':	// zombie
					m_zombieStarts.emplace_back(x * TILE_SIZE, y * TILE_SIZE);
					break;

				default:	// empty
					break;
			}
		}
	}

	m_spriteBatch.End();
}


Level::~Level() {
}


void Level::Render() {
	m_spriteBatch.Render();
}
