#pragma once

#include "GLTexture.h"
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include "Vertex.h"

namespace MyGameEngine {

class Particle2D
{
	friend class ParticleBatch2D;

public:
	Particle2D() = default;
	~Particle2D() = default;

	Particle2D(const glm::vec2& position, const glm::vec2& velocity,
		const Color& color, float size) :
		position(position), velocity(velocity), color(color), size(size) {
	}


private:
	void update(float deltaTime);

	glm::vec2	position = glm::vec2(0.0f);
	glm::vec2	velocity = glm::vec2(0.0f);
	float		size = 0.0f;
	Color		color = Color(255, 255, 255, 255);
	float		lifetime = 0.0f;

	bool isActive() { return lifetime > 0.0f; }
	glm::vec4 rect() {
		return glm::vec4(position.x - size, position.y - size, 2 * size, 2 * size);
	}
};


class ParticleBatch2D
{
public:
	ParticleBatch2D(int maxParticles, float particleLifetime, GLTexture texture) :
		m_maxParticles(maxParticles),
		m_particleLifetime(particleLifetime),
		m_particleTexture(texture) {
		m_particles = new Particle2D[maxParticles];
	}
	~ParticleBatch2D() { delete[] m_particles; }

	void addParticle(const glm::vec2& position, const glm::vec2& velocity,
		const Color& color, float size);

	void update(float deltaTime);
	void draw(SpriteBatch& spriteBatch);

private:
	int findFreeParticle();

	Particle2D* m_particles = nullptr;
	int			m_maxParticles = 0;
	int			m_lastFreeParticle = 0;

	float		m_particleLifetime = 0.0f;
	GLTexture	m_particleTexture;
};

}
