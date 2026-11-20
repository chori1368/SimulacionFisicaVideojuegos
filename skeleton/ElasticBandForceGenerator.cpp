#include "ElasticBandForceGenerator.h"

ElasticBandForceGenerator::ElasticBandForceGenerator(double k, double resting_length, Particle* other)
	: SpringForceGenerator(k, resting_length, other)
{
}

void ElasticBandForceGenerator::applyForce(Particle* particle, double t)
{
	if (!particle || !_other) return;

	Vector3D relative_pos_vector = _other->getPos() - particle->getPos();
	const float length = relative_pos_vector.magnitude();
	const float delta_x = length - _resting_length;

	// La goma solo aplica fuerza cuando se estira (delta_x > 0)
	if (delta_x > 0.0f) {
		Vector3D force = relative_pos_vector * delta_x * _k;
		particle->addForce(force);
	}
	// Cuando se comprime (delta_x <= 0), no aplica fuerza
}