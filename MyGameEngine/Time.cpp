#include "Time.h"

#include <SDL/SDL.h>

#include <numeric>
#include <vector>

#include <iostream>

namespace MyGameEngine {

Time::Time() {
}

Time::~Time() {
}

void Time::Init(float maxFPS /* = 60 */) {
	m_maxFPS = maxFPS;
	m_startTime = 0;
}

void Time::BeginFrame() {
	m_prevStartTime = m_startTime;
	m_startTime = SDL_GetTicks();
}

void Time::EndFrame() {
	unsigned int frameTime = SDL_GetTicks() - m_startTime;

	if (1000 / m_maxFPS > frameTime) {
		SDL_Delay(1000 / m_maxFPS - frameTime);
	}

	frameTime = SDL_GetTicks() - m_startTime;
	CalculateFPS(frameTime);
}


float Time::DeltaTime() {
	return static_cast<float>(m_startTime - m_prevStartTime) / 1000.0f;
}


void Time::CalculateFPS(unsigned int frameTime) {

	static const int N_SAMPLES = 10;
	static std::vector<unsigned int> frameTimes(N_SAMPLES, 0);
	static int currentFrame = 0;
	
	frameTimes[currentFrame % N_SAMPLES] = frameTime;

	currentFrame++;
	int count = (currentFrame < N_SAMPLES) ? currentFrame : N_SAMPLES;

	float mean = (float)std::accumulate(frameTimes.begin(), frameTimes.end(), 0) / count;

	if (mean == 0)	m_FPS = NAN;
	else			m_FPS = 1000 / mean;
}

}
