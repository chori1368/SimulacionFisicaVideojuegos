#include "forceGenerator.h"
#include <algorithm>

void forceGenerator::addAfeccted(Particle* particula) {
	if (particula) particulas.push_back(particula);
}

void forceGenerator::removeAfeccted(Particle* particula) {
	particulas.erase(std::remove(particulas.begin(), particulas.end(), particula), particulas.end());
}

void forceGenerator::update(double t) {
	for (auto it = particulas.begin(); it != particulas.end();) {
		Particle* p = *it;
		if (!p) {
			it = particulas.erase(it);
			continue;
		}
		applyForce(p, t);
		++it;
	}
}