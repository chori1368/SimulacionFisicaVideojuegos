#include "Proyectile.h"

Proyectile::Proyectile(Vector3D pos, Vector3D _vel, float masa, Vector3D xlr8, float dumping, Integrator newIntegrator)
	: Particle(pos, _vel, xlr8, dumping, newIntegrator) {
	mass = masa;
}