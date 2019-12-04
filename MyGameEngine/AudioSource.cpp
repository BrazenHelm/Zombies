#include "AudioSource.h"

#include <iostream>

#include "MyErrors.h"

namespace MyGameEngine::Audio {

AudioSource::AudioSource()
{
}


AudioSource::~AudioSource()
{
}


void AudioSource::init() {
	// Parameters determine the file types that can be read
	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
		FatalError("Mix_Init error: " + std::string(Mix_GetError()));
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		FatalError("Mix_OpenAudio error: " + std::string(Mix_GetError()));
	}
	Mix_AllocateChannels(16);
	m_isInit = true;
}


void AudioSource::destroy() {
	if (m_isInit) {
		m_isInit = false;
		Mix_Quit();
	}
}


Music AudioSource::loadMusic(const std::string& path) {

	Music music;

	if (m_musicCache.count(path) == 0) {
		// Load new music
		Mix_Music* mixMusic = Mix_LoadMUS(path.c_str());
		if (mixMusic == nullptr) {
			FatalError("Mix_LoadMUS error: " + std::string(Mix_GetError()));
		}
		m_musicCache.emplace(path, mixMusic);
		music.m_pMusic = mixMusic;
	}
	else {
		// Music is already cached
		music.m_pMusic = m_musicCache[path];
	}
	return music;
}


SoundEffect AudioSource::loadSound(const std::string& path) {

	SoundEffect sound;

	if (m_soundCache.count(path) == 0) {
		// Load new sound
		Mix_Chunk* mixChunk = Mix_LoadWAV(path.c_str());
		if (mixChunk == nullptr) {
			FatalError("Mix_LoadWAV error: " + std::string(Mix_GetError()));
		}
		m_soundCache.emplace(path, mixChunk);
		sound.m_pChunk = mixChunk;
	}
	else {
		// Music is already cached
		sound.m_pChunk = m_soundCache[path];
	}
	return sound;
}

}
