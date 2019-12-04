#include "SoundEffect.h"

#include "MyErrors.h"

namespace MyGameEngine::Audio {


SoundEffect::SoundEffect() {
}


SoundEffect::~SoundEffect() {
}


void SoundEffect::play(int loops /*= 1*/) {
	if (Mix_PlayChannel(-1, m_pChunk, loops - 1) == -1) {
		FatalError("Mix_PlayChannel error: " + std::string(Mix_GetError()));
	}
}


}