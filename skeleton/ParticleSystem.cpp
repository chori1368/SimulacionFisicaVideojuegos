#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Vector3D Dir, Vector3D Pos, float Limit,float velvar, float dirvar, float posvar, float lifevar, float genvar) :
	pos(Pos),dir(Dir),limit(Limit){

	pos_dist = std::normal_distribution<float>(0.0f, posvar);
	speed_dist = std::normal_distribution<float>(5.0f, velvar);
	dir_dist = std::normal_distribution<float>(0.0f, dirvar);
	lifetime_dist = std::normal_distribution<float>(4.0f, lifevar);

	part_gen_dist = std::normal_distribution<float>(1, genvar);
}

void ParticleSystem::createParticle() {
	Vector3D const Pos = Vector3D(pos.getX() + pos_dist(generator), pos.getY() + pos_dist(generator), pos.getZ() + pos_dist(generator));
	Vector3D const vel = Vector3D(dir.getX() + dir_dist(generator), dir.getY() + dir_dist(generator), dir.getZ() + dir_dist(generator)) * speed_dist(generator);
	particles.push_back(new Particle(Pos, vel, Vector3D(0.0f, -9.8f, 0.0f), 1, lifetime_dist(generator)));
}

void ParticleSystem::update(double t) {
	for (auto it = particles.begin(); it != particles.end(); ) {
		Particle* p = *it;
		if (!p) {
			it = particles.erase(it);
			continue;
		}
		float l = p->getlife();               // usar float, no int
		if (l > 0.0f) {
			p->setlife(l - t);
			p->integrate(t, Integrator::SemiEuler);
			++it;
		}
		else {
			delete p;                         // destruir el objeto
			it = particles.erase(it);         // y eliminar el puntero del vector
		}
	}
	int part_to_gen = (int)part_gen_dist(generator);
	for (int i = 0; i < part_to_gen; ++i) {
		createParticle();
	}
}

void ParticleSystem::cleanup() {
	for (Particle* p : particles) {
		if (p)
			delete p;
	}
}