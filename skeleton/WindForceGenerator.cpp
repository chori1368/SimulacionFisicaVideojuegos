#include "windForceGenerator.h"
#include "Particle.h"
#include <cmath>

windForceGenerator::windForceGenerator(const Vector3D& position, float radius, 
	const Vector3D& windVel, float k1, float k2)
	: position(position), radius(radius), windVelocity(windVel), k1(k1), k2(k2) {
}

bool windForceGenerator::isInInfluenceZone(const Vector3D& particlePos) const {
	Vector3D diff = particlePos - position;
	float distance = diff.magnitude();
	return distance <= radius;
}

void windForceGenerator::applyForce(Particle* particula, double t) {
	if (!particula) return;

	// Solo aplicar si la partícula está en la zona de influencia
	if (!isInInfluenceZone(particula->getPos())) return;

	// Diferencia de velocidad: v_viento - v_particula
	Vector3D velDiff = windVelocity - particula->getVelocity();
	
	// Magnitud de la diferencia de velocidad
	float velDiffMag = velDiff.magnitude();

	// F_v = k1 * (v_viento - v_particula) + k2 * ||v_viento - v_particula|| * (v_viento - v_particula)
	Vector3D windForce = velDiff * k1;
	
	if (k2 > 0.0f && velDiffMag > 0.0f) {
		windForce += velDiff * (k2 * velDiffMag);
	}

	particula->addForce(windForce);
}

