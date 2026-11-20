#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other) : _k(k),
_resting_length(resting_length), _other (other){}

void SpringForceGenerator::applyForce(Particle* particle, double t) {
	Vector3D relative_pos_vector = _other->getPos() - particle->getPos();
	Vector3D force;

	const float length = relative_pos_vector.magnitude();
	const float delta_x = length - _resting_length;

	force = relative_pos_vector * delta_x * _k;

	particle->addForce(force);
}