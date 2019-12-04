#pragma once

#include <SDL/SDL_mixer.h>


namespace MyGameEngine::Audio {


class SoundEffect
{
public:
	friend class AudioSource;

	SoundEffect();
	~SoundEffect();

	// Plays the sound file
	// @param loops: if loops is -1 loop indefinitely, otherwise play loops times
	void play(int loops = 1);

private:
	Mix_Chunk* m_pChunk = nullptr;
};

}
