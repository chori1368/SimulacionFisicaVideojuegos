#include "ParticleSystem.h"
#include "forceGenerator.h"
#include <algorithm>

ParticleSystem::ParticleSystem(Vector3D Dir, Vector3D Pos, float Limit, float mass, forceGenerator* gravityGen) :
	pos(Pos), dir(Dir), limit(Limit), masa(mass), gravityGen(gravityGen) {

	pos_dist = std::normal_distribution<float>(0.0f, 0.1f);
	speed_dist = std::normal_distribution<float>(30.0f, 1.0f);
	dir_dist = std::normal_distribution<float>(0.0f, 0.05);
	lifetime_dist = std::normal_distribution<float>(6.0f, 1.0f);

	part_gen_dist = std::normal_distribution<float>(2, 1.0);
	maxParticles = 500;

	// Agregar gravedad si existe
	if (gravityGen) {
		generators.push_back(gravityGen);
	}
}

void ParticleSystem::addForceGenerator(forceGenerator* gen) {
	if (gen) {
		generators.push_back(gen);
	}
}

void ParticleSystem::removeForceGenerator(forceGenerator* gen) {
	if (gen) {
		auto it = std::find(generators.begin(), generators.end(), gen);
		if (it != generators.end()) {
			generators.erase(it);
		}
	}
}

void ParticleSystem::createParticle() {
	Vector3D const Pos = Vector3D(pos.getX() + pos_dist(generator), pos.getY() + pos_dist(generator), pos.getZ() + pos_dist(generator));
	Vector3D const vel = Vector3D(dir.getX() + dir_dist(generator), dir.getY() + dir_dist(generator), dir.getZ() + dir_dist(generator)) * speed_dist(generator);
	Particle* p;
		p = new Particle(Pos, vel, Vector3D(0.0f, 0.0f, 0.0f), masa, lifetime_dist(generator));
	particles.push_back(p);

	// Registrar en los generadores
	for (forceGenerator* gen : generators) {
		if (gen) gen->addAfeccted(p);
	}
}

bool ParticleSystem::isWithinLimit(const Vector3D& particlePos) {
	float half_limit = limit / 2.0f;

	// Comprobar si está dentro del cubo centrado en pos con arista limit
	if (abs(particlePos.getX() - pos.getX()) > half_limit) return false;
	if (abs(particlePos.getY() - pos.getY()) > half_limit) return false;
	if (abs(particlePos.getZ() - pos.getZ()) > half_limit) return false;

	return true;
}

void ParticleSystem::update(double t) {
	for (auto it = particles.begin(); it != particles.end(); ) {
		Particle* p = *it;
		if (!p) {
			it = particles.erase(it);
			continue;
		}
		float l = p->getlife();
		if (l > 0.0f && isWithinLimit(p->getPos())) {
			p->setlife(l - t);
			p->integrate(t, Integrator::SemiEuler);
			++it;
		}
		else {
			// Remover de los generadores
			for (forceGenerator* gen : generators) {
				if (gen) gen->removeAfeccted(p);
			}
			delete p;
			it = particles.erase(it);
		}
	}
	int part_to_gen = (int)part_gen_dist(generator);
	for (int i = 0; i < part_to_gen; ++i) {
		if (particles.size() < maxParticles)
			createParticle();
	}
}

void ParticleSystem::cleanup() {
	for (Particle* p : particles) {
		if (p) {
			for (forceGenerator* gen : generators) {
				if (gen) gen->removeAfeccted(p);
			}
			delete p;
		}
	}
	particles.clear();
}