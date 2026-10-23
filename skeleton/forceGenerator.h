#pragma once
#include <vector>
#include "Particle.h"

class forceGenerator
{
public:
	forceGenerator() = default;
	virtual ~forceGenerator() = default;

	void addAfeccted(Particle* particula);
	void removeAfeccted(Particle* particula);
	void update(double t);

protected:
	virtual void applyForce(Particle* particula, double t) = 0;
	std::vector<Particle*> particulas;
};