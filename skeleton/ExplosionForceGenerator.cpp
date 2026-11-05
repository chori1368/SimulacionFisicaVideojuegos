#include "ExplosionForceGenerator.h"
#include "Particle.h"
#include <cmath>

ExplosionForceGenerator::ExplosionForceGenerator(const Vector3D& center, float radius, float K, float tau)
	: center(center), radius(radius), K(K), tau(tau), explosionTime(-1.0) {
}

void ExplosionForceGenerator::triggerExplosion() {
	explosionTime = 0.0;
	setEnabled(true);  // ACTIVAR la explosión
}

bool ExplosionForceGenerator::isActive() const {
	if (explosionTime < 0.0) return false;
	return explosionTime < 4.0f * tau;
}

double ExplosionForceGenerator::getElapsedTime() const {
	if (explosionTime < 0.0) return 0.0;
	return explosionTime;
}

void ExplosionForceGenerator::update(double t) {
	if (isActive()) {
		explosionTime += t;  // Incrementar UNA SOLA VEZ
	} else if (explosionTime >= 0.0) {
		setEnabled(false);  // Desactivar cuando termina
	}
	forceGenerator::update(t);
}

void ExplosionForceGenerator::applyForce(Particle* particula, double t) {
	if (particula && isActive()) {

		Vector3D diff = particula->getPos() - center;
		float r = diff.magnitude();


		// Si está fuera del radio de influencia, no aplicar fuerza
		if (r > radius || r < 0.001f) return;

		// Calcular la fuerza según la fórmula:
		// Fe⃗ = (K / r²) * [(x - xc), (y - yc), (z - zc)] * e^(-t/tau)

		// Factor de atenuación exponencial
		float attenuationFactor = std::exp(-explosionTime / tau);

		// Magnitud de la fuerza radial
		float forceMagnitude = (K / (r * r)) * attenuationFactor;

		// Dirección radial (desde el centro hacia afuera)
		Vector3D forceDirection = diff.normalize();

		// Fuerza total
		Vector3D explosionForce = forceDirection * forceMagnitude;

		particula->addForce(explosionForce);
	}
}