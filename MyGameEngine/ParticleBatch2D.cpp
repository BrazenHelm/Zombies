#include "ParticleBatch2D.h"

namespace MyGameEngine {





void ParticleBatch2D::addParticle(const glm::vec2& position, const glm::vec2& velocity,
	const Color& color, float size) {

	int particleIndex = findFreeParticle();
	auto& p = m_particles[particleIndex];
	p = Particle2D(position, velocity, color, size);
	p.lifetime = m_particleLifetime;
}


void ParticleBatch2D::update(float deltaTime) {
	for (int i = 0; i < m_maxParticles; i++) {
		if (m_particles[i].isActive()) {
			m_updateFunction(m_particles[i], deltaTime);
		}
	}
}


void ParticleBatch2D::draw(SpriteBatch& spriteBatch) {
	glm::vec4 uv(0, 0, 1, 1);
	for (int i = 0; i < m_maxParticles; i++) {
		auto& p = m_particles[i];
		if (p.isActive()) {
			spriteBatch.Draw(p.rect(), uv, m_particleTexture.id, 0.0f, p.color);
		}
	}
}


int ParticleBatch2D::findFreeParticle() {

	for (int i = m_lastFreeParticle; i < m_maxParticles; i++) {
		if (!m_particles[i].isActive()) {
			m_lastFreeParticle = i + 1;
			return i;
		}
	}
	for (int i = 0; i < m_lastFreeParticle; i++) {
		if (!m_particles[i].isActive()) {
			m_lastFreeParticle = i + 1;
			return i;
		}
	}
	// if you reached here, no particles are free
	return m_lastFreeParticle++;
}


}
