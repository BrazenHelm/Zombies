#pragma once

#include <SDL/SDL_mixer.h>


namespace MyGameEngine::Audio {


class Music
{
public:
	friend class AudioSource;

	Music();
	~Music();

	/**
	* Plays the music file
	* param loops: the number of times to loop. -1 loops indefinitely
	*/
	void play(int loops = 1);

	static void stop();
	static void pause();
	static void resume();

private:
	Mix_Music* m_pMusic = nullptr;

};

}
