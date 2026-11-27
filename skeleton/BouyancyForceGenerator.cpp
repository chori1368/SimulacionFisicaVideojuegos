#include "BouyancyForceGenerator.h"

BouyancyForceGenerator::BouyancyForceGenerator(float h, float v, float d, Particle* liquid) :
 _height(h), _volume(v), _liquid_density(d), _liquid_particle(liquid){}

void BouyancyForceGenerator::applyForce(Particle* particle, double t) {
	float h = particle->getPos().getY();
	float h0 = _liquid_particle->getPos().getY();

	Vector3D f(0, 0, 0);
	float immersed = 0.0;
	if (h - h0 > _height * 0.5) {
		immersed = 0.0;
	} else if (h0 - h > _height * 0.5) {
		immersed = 1.0;
	} else {
		immersed = (h0 - h) / _height + 0.5;
	}
	f.setY(_liquid_density * _volume * immersed * _gravity);

	particle->addForce(f);
}