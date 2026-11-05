#include "forceGenerator.h"
#include <algorithm>

void forceGenerator::addAfeccted(Particle* particula) {
	if (particula) {
		auto it = std::find(particulas.begin(), particulas.end(), particula);
		if (it == particulas.end()) {
			particulas.push_back(particula);
		}
	}
}

void forceGenerator::removeAfeccted(Particle* particula) {
	if (!particula) return;
	auto it = std::find(particulas.begin(), particulas.end(), particula);
	if (it != particulas.end()) {
		particulas.erase(it);
	}
}

void forceGenerator::update(double t) {
	// Si no está activado, no hacer nada
	if (enabled) {

		//Limpiar punteros nulos Y crear nueva lista válida
		std::vector<Particle*> validParticles;
		for (Particle* p : particulas) {
			if (p != nullptr) {
				validParticles.push_back(p);
				applyForce(p, t);
			}
		}
		particulas = validParticles;  // Reemplazar con lista limpia
	}
}