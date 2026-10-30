#include "gravityForceGenerator.h"

gravityForceGenerator::gravityForceGenerator(const Vector3D& gravityAccel)
	: gravity(gravityAccel) {}

void gravityForceGenerator::applyForce(Particle* particula, double t) {
	if (particula)
		particula->addForce(gravity * particula->getMass());
}