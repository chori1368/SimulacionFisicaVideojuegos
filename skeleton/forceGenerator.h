#pragma once
#include "Particle.h"

enum Force
{
	Gravity,
	Wind,
	whirlwind
};

class forceGenerator
{
public:
	forceGenerator(Force fuerza);
	void addAfeccted(Particle* particula);
	void removeAfeccted(Particle* particula);
	void update(double t);
private:
	Force fuerza;
	std::vector<Particle*> particulas;
};