#pragma once
#include "SpringForceGenerator.h"

class ElasticBandForceGenerator : public SpringForceGenerator
{
public:
	ElasticBandForceGenerator(double k, double resting_length, Particle* other);
	virtual ~ElasticBandForceGenerator() = default;

	void applyForce(Particle* particle, double t) override;
};