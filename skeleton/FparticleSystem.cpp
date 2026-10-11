#include "FparticleSystem.h"

FparticleSystem::FparticleSystem(Vector3D Dir, Vector3D Pos, float Limit) :
	ParticleSystem(Dir, Pos, Limit), lastDeathPos(Pos) {

	pos_dist = std::normal_distribution<float>(2.0f, 0.5f);
	speed_dist = std::normal_distribution<float>(3.0f, 0.5f);
	dir_dist = std::normal_distribution<float>(5.0f, 5.0f);
	lifetime_dist = std::normal_distribution<float>(1.0f, 0.3f);

	part_gen_dist = std::normal_distribution<float>(3.0f, 1.0f);
	maxParticles = 500;

	createParticle();
	speed_dist = std::normal_distribution<float>(0.5f, 0.5f);
}

void FparticleSystem::createParticle() {
	Vector3D const Pos = Vector3D(pos.getX() + pos_dist(generator), pos.getY() + pos_dist(generator), pos.getZ() + pos_dist(generator));
	Vector3D const vel = Vector3D(dir.getX() + dir_dist(generator), dir.getY() + dir_dist(generator), dir.getZ() + dir_dist(generator)) * speed_dist(generator);
	particles.push_back(new Particle(Pos, vel, Vector3D(0.0f, 0.0f, 0.0f), 1, lifetime_dist(generator)));
}

void FparticleSystem::createParticleAtPos(const Vector3D& deathPos) {
	Vector3D const Pos = Vector3D(deathPos.getX() + pos_dist(generator), deathPos.getY() + pos_dist(generator), deathPos.getZ() + pos_dist(generator));
	Vector3D const vel = Vector3D(dir.getX() + dir_dist(generator), dir.getY() + dir_dist(generator), dir.getZ() + dir_dist(generator)) * speed_dist(generator);
	particles.push_back(new Particle(Pos, vel, Vector3D(0.0f, 0.0f, 0.0f), 1, lifetime_dist(generator)));
}

void FparticleSystem::update(double t) {
	int particles_killed = 0;
	for (auto it = particles.begin(); it != particles.end(); ) {
		Particle* p = *it;
		if (!p) {
			it = particles.erase(it);
			continue;
		}
		float l = p->getlife();
		if (l > 0.0f) {
			p->setlife(l - t);
			p->integrate(t, Integrator::SemiEuler);
			++it;
		}
		else {
			lastDeathPos = p->getPos();
			delete p;
			it = particles.erase(it);
			++particles_killed;
		}
	}
	for (int k = 0; k < particles_killed; ++k) {
		int part_to_gen = (int)part_gen_dist(generator);
		for (int i = 0; i < part_to_gen; ++i) {
			if (particles.size() < maxParticles)
				createParticleAtPos(lastDeathPos);
		}
	}
}