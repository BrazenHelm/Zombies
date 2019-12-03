#pragma once

namespace MyGameEngine {

class Time
{
public:
	Time();
	~Time();

	void Init(float maxFPS = 60);
	void BeginFrame();
	void EndFrame();

	float GetFPS() { return m_FPS; }

	// Time the previous frame took in seconds
	float DeltaTime();

private:
	float m_maxFPS;
	float m_FPS;

	unsigned int m_startTime;
	unsigned int m_prevStartTime;

	void CalculateFPS(unsigned int frameTicks);
};

}
