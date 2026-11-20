#pragma once

#include "forceGenerator.h"

class SpringForceGenerator : public forceGenerator {
public:
	SpringForceGenerator(double k, double resting_length, Particle* other);

	void applyForce(Particle* particula, double t) override;

	inline void setK(double k) { _k = k; };

protected:
	double _k;
	double _resting_length;
	Particle* _other;
};

