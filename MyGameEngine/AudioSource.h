#pragma once

#include <SDL/SDL_mixer.h>
#include <map>
#include <string>

#include "Music.h"
#include "SoundEffect.h"


namespace MyGameEngine::Audio {

class AudioSource
{
public:
	AudioSource();
	~AudioSource();

	void init();
	void destroy();

	Music		loadMusic(const std::string& path);
	SoundEffect loadSound(const std::string& path);

private:
	std::map<std::string, Mix_Music*> m_musicCache;
	std::map<std::string, Mix_Chunk*> m_soundCache;

	bool m_isInit = false;
};

}

