#pragma once
#include "particle.h"
class Proyectile : public Particle
{
public:
	Proyectile(Vector3D Pos, Vector3D vel, float masa, Vector3D xlr8 = { 0,0,0 }, float dumping = 0.99, Integrator newIntegrator = Integrator::SemiEuler);
	~Proyectile() {};
protected:
	float mass;
};

