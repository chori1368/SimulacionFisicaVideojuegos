#pragma once

#include "forceGenerator.h"

class BouyancyForceGenerator : public forceGenerator {
public:
	BouyancyForceGenerator(float h, float v, float d, Particle* liquid);

	virtual void applyForce(Particle* particle, double t) override;

	virtual ~BouyancyForceGenerator();

protected:
	float _height;
	float _volume;
	float _liquid_density;
	float _gravity = 9.8;

	Particle* _liquid_particle; // For representation
};

