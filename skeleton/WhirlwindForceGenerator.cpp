#include "WhirlwindForceGenerator.h"
#include "Particle.h"
#include <cmath>

WhirlwindForceGenerator::WhirlwindForceGenerator(const Vector3D& center, float radius, float K,
	float k1, float k2)
	: windForceGenerator(center, radius, Vector3D(0.0f), k1, k2), center(center), K(K) {
	// La velocidad inicial no importa porque se calculará según posición
}

Vector3D WhirlwindForceGenerator::calculateWhirlwindVelocity(const Vector3D& particlePos) const {
	Vector3D diff = particlePos - center;

	// Distancia en el plano XZ (ignorar Y)
	float dx = particlePos.getX() - center.getX();
	float dz = particlePos.getZ() - center.getZ();
	float distanceXZ = std::sqrt(dx * dx + dz * dz);

	// Si está muy cerca del centro, velocidad casi nula
	if (distanceXZ < 0.1f) {
		return Vector3D(0.0f, 0.0f, 0.0f);
	}

	// Vector tangencial perpendicular al radio (normalizado)
	// Rotación en sentido antihorario visto desde arriba
	float tangentX = -dz / distanceXZ;
	float tangentZ = dx / distanceXZ;

	// Velocidad tangencial escalonada por distancia (efecto de remolino)
	Vector3D whirlwindVel = Vector3D(
		K * distanceXZ * tangentX,
		0.0f,
		K * distanceXZ * tangentZ
	);

	return whirlwindVel;
}

void WhirlwindForceGenerator::applyForce(Particle* particula, double t) {
	if (!particula) return;

	// Solo aplicar si la partícula está en la zona de influencia
	if (!isInInfluenceZone(particula->getPos())) return;

	// Calcular velocidad del torbellino según la posición
	Vector3D whirlwindVel = calculateWhirlwindVelocity(particula->getPos());

	// Diferencia de velocidad: v_torbellino - v_particula
	Vector3D velDiff = whirlwindVel - particula->getVelocity();
	
	// Magnitud de la diferencia de velocidad
	float velDiffMag = velDiff.magnitude();

	// F_v = k1 * (v_torbellino - v_particula) + k2 * ||v_torbellino - v_particula|| * (v_torbellino - v_particula)
	Vector3D whirlwindForce = velDiff * k1;
	
	if (k2 > 0.0f && velDiffMag > 0.0f) {
		whirlwindForce += velDiff * (k2 * velDiffMag);
	}

	particula->addForce(whirlwindForce);
}
