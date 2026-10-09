#include <cmath>
#include "Particle.h"

Particle::Particle(const Vector3D& Pos, const Vector3D& Xlr8)
	: pose(Pos), vel(0, 0, 0), accel(Xlr8), poset(Pos) {
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(0.5f), nullptr), &pose, Vector4(0.8f, 0.2f, 0.3f, 1.f));
	renderItem->addReference();
}
Particle::~Particle() {
	renderItem->release();
}

void Particle::integrate(double t, Integrator integrator) {
	// Euler
	switch (integrator) {
		case (Integrator::Euler):
		{
			integrateEuler(t);
			break;
		}
		case (Integrator::SemiEuler):
		{
			integrateSemiEuler(t);
			break;
		}
		case (Integrator::Verlet):
		{
			integrateVerlet(t);
			break;
		}
	}
}

void Particle::integrateEuler(double t)
{
	// Euler

	pose.p = pose.p + vel * t;

	vel = vel + accel * t;

	vel = vel * std::pow(DAMPING, t); // Esto es para que el damping dependa también del delta. Usamos pow porque hay que contrarestarlo de forma exponencial.

	accel = Vector3D(0, 0, 0);
}

void Particle::integrateSemiEuler(double t)
{
	// Euler semi-implicito

	vel = vel + accel * t;

	vel = vel * std::pow(DAMPING, t); // Esto es para que el damping dependa también del delta. Usamos pow porque hay que contrarestarlo de forma exponencial.

	pose.p = pose.p + vel * t;

	accel = Vector3D(0, 0, 0);
}

void Particle::integrateVerlet(double t)
{
	const Vector3D posDelta = (2 * pose.p - poset);

	poset = pose.p;

	pose.p = posDelta + accel * t * t;

	accel = Vector3D(0, 0, 0);
}