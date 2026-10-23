#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"

	enum Integrator
{
	Euler,
	SemiEuler,
	Verlet
};
constexpr float DAMPING = 0.99f;

class Particle
{
public:
	Particle(const Vector3D& Pos, const Vector3D& Vel, const Vector3D& Xlr8, const float Mass, const float life);
	virtual ~Particle();

	virtual void integrate(double t, Integrator i);

	virtual float getlife() { return life; };
	virtual void setlife(float Life) { life = Life; };
	virtual Vector3D getPos() { return pose.p; };

	virtual float getMass() const { return mass; }
	virtual void setAcceleration(const Vector3D& a) { accel = a; }
	virtual void addForce(const Vector3D& f) { force += f; }
	virtual void clearForces() { force = Vector3D(0.0f); }

protected:
	Vector3D vel;
	physx::PxTransform pose;
	Vector3D poset;

	Vector3D accel;
	Vector3D force;

	RenderItem* renderItem;
	float mass;
	float life;

	virtual void integrateEuler(double t);
	virtual void integrateSemiEuler(double t);
	virtual void integrateVerlet(double t);
};