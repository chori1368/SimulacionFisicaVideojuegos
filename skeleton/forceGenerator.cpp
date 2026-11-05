#include "forceGenerator.h"
#include <algorithm>

void forceGenerator::addAfeccted(Particle* particula) {
	if (particula) particulas.push_back(particula);
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

		// Limpiar punteros nulos (por si acaso)
		particulas.erase(
			std::remove_if(particulas.begin(), particulas.end(),
				[](Particle* p) { return p == nullptr; }),
			particulas.end()
		);

		for (Particle* p : particulas) {
			if (p) { // Validación extra
				applyForce(p, t);
			}
		}
	}
}