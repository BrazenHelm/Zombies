#pragma once

#include <string>
#include <vector>

#include <MyGameEngine/SpriteBatch.h>

class Level
{
public:
	Level(const std::string& filename);
	~Level();

	void Render();

	glm::vec2				PlayerStart()	const { return m_playerStart; }
	std::vector<glm::vec2>	ZombieStarts()	const { return m_zombieStarts; }

private:
	const int TILE_SIZE = 32;

	int							m_nHumans;
	glm::vec2					m_playerStart;
	std::vector<glm::vec2>		m_zombieStarts;
	std::vector<std::string>	m_levelData;

	MyGameEngine::SpriteBatch	m_spriteBatch;
};

