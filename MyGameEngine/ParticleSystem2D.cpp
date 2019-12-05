#include "ParticleSystem2D.h"

#include "ParticleBatch2D.h"
#include "SpriteBatch.h"

namespace MyGameEngine {

ParticleSystem2D::~ParticleSystem2D() {
	for (ParticleBatch2D* batch : m_pParticleBatches) {
		delete batch;
	}
}


void ParticleSystem2D::addParticleBatch(ParticleBatch2D* batch) {
	m_pParticleBatches.emplace_back(batch);
}


void ParticleSystem2D::update(float deltaTime) {
	for (ParticleBatch2D* batch : m_pParticleBatches) {
		batch->update(deltaTime);
	}
}


void ParticleSystem2D::draw(SpriteBatch& spriteBatch) {
	for (ParticleBatch2D* batch : m_pParticleBatches) {
		batch->draw(spriteBatch);
	}
}

}


