#pragma once

#include <vector>

namespace MyGameEngine {

class ParticleBatch2D;
class SpriteBatch;

class ParticleSystem2D
{
public:
	ParticleSystem2D() = default;
	~ParticleSystem2D();

	/**
	* After adding a particle batch, the ParticleSystem2D becomes responsible for deallocation.
	*/
	void addParticleBatch(ParticleBatch2D* batch);

	void update(float deltaTime);
	void draw(SpriteBatch& spriteBatch);

private:
	std::vector<ParticleBatch2D*> m_pParticleBatches;
};

}



