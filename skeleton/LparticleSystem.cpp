#include "LparticleSystem.h"
#include "forceGenerator.h"

LparticleSystem::LparticleSystem(Vector3D Dir, Vector3D Pos, float Limit, float mass, forceGenerator* gen) :
	ParticleSystem(Dir, Pos, Limit, mass, gen) {

	pos_dist = std::normal_distribution<float>(20.0f, 10.0f);
	speed_dist = std::normal_distribution<float>(15.0f, 1.0f);
	dir_dist = std::normal_distribution<float>(0.0f, 0.01f);
	lifetime_dist = std::normal_distribution<float>(6.0f, 1.0f);

	part_gen_dist = std::normal_distribution<float>(1.0f, 0.01f);
	maxParticles = 100;
}

void LparticleSystem::createParticle() {
	Vector3D const Pos = Vector3D(pos.getX() + pos_dist(generator), pos.getY(), pos.getZ() + pos_dist(generator));
	Vector3D const vel = Vector3D(dir.getX() + dir_dist(generator), dir.getY() + dir_dist(generator), dir.getZ() + dir_dist(generator)) * speed_dist(generator);
	Particle* p = new Particle(Pos, vel, Vector3D(0.0f, 0.0f, 0.0f), masa, lifetime_dist(generator));
	particles.push_back(p);

	// Registrar en TODOS los generadores
	for (forceGenerator* gen : generators) {
		if (gen) gen->addAfeccted(p);
	}
}