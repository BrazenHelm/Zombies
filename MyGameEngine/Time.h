#pragma once

namespace MyGameEngine {

class FPSLimiter
{
public:
	FPSLimiter();
	~FPSLimiter();

	void Init(float maxFPS = 60);
	void BeginFrame();
	void EndFrame();

	float GetFPS() { return m_FPS; }

private:
	float m_maxFPS;
	float m_FPS;

	unsigned int m_startTime;

	void CalculateFPS(unsigned int frameTicks);
};

}
