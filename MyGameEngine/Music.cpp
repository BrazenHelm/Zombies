#include "Music.h"

#include "MyErrors.h"


namespace MyGameEngine::Audio {

Music::Music() {
}


Music::~Music() {
}


void Music::play(int loops /*= 1*/) {
	if (Mix_PlayMusic(m_pMusic, loops) == -1) {
		FatalError("Mix_PlayMusic error: " + std::string(Mix_GetError()));
	}
}

void Music::stop() { Mix_HaltMusic(); }

void Music::pause() { Mix_PauseMusic(); }

void Music::resume() { Mix_ResumeMusic(); }

}
