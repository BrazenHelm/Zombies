#include "Level.h"

#include <fstream>
#include <iostream>

#include <MyGameEngine/MyErrors.h>
#include <MyGameEngine/ResourceManager.h>


Level::Level(const std::string& filename) {

	std::ifstream file;
	file.open(filename);

	if (file.fail()) {
		MyGameEngine::FatalError("Could not load level data " + filename);
	}

	std::string buffer;
	file >> m_nHumans;
	std::getline(file, buffer);	// throw away remainder of first line

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
	MyGameEngine::Color white(255, 255, 255, 255);

	for (size_t y = 0; y < m_levelData.size(); y++) {
		for (size_t x = 0; x < m_levelData[y].size(); x++) {

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
