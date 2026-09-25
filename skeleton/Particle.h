#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"

enum Integrator
{
	Euler,
	SemiEuler,
	Verlet
};

class Particle
{
public:
	Particle(Vector3D Pos, Vector3D vel,Vector3D xlr8 = {0,0,0}, float dumping = 0.98, Integrator newIntegrator = Integrator::SemiEuler);
	~Particle();

	void integrate(double t);
private:
	Vector3D vel;
	physx::PxTransform pose;
	physx::PxTransform poset = { 0,0,0 };
	Vector3D accel;
	float damping;
	RenderItem* renderItem;
	Integrator integrator;
	void integrateEuler(double t);
	void integrateSemiEuler(double t);
	void integrateVerlet(double t);
};