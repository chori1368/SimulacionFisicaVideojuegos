#include <cmath>
#include "Particle.h"

Particle::Particle(const Vector3D& Pos, const Vector3D& Vel, const Vector3D& Xlr8, const float Mass, const float Life)
	: pose(Pos), vel(Vel), baseAccel(Xlr8), accel(Xlr8), force(0.0f), poset(Pos), mass(Mass), life(Life) {
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(0.5f), nullptr), &pose, Vector4(1.0f, 0.43f, 0.0f, 1.f));
}

Particle::~Particle()
{
    if (renderItem) {
        renderItem->release();
        renderItem = nullptr;
    }
}

void Particle::integrate(double t, Integrator integrator) {
	// Comenzar con la aceleración base (gravedad)
	accel = baseAccel;
	
	// Añadir fuerzas
	accel += force / mass;
	
	switch (integrator) {
	case (Integrator::Euler):
		integrateEuler(t);
		break;
	case (Integrator::SemiEuler):
		integrateSemiEuler(t);
		break;
	case (Integrator::Verlet):
		integrateVerlet(t);
		break;
	}

	clearForces();
}

void Particle::integrateEuler(double t)
{
	// Euler

	pose.p = pose.p + vel * t;

	vel = vel + accel * t;

	vel = vel * std::pow(DAMPING, t);

}

void Particle::integrateSemiEuler(double t)
{
	// Euler semi-implicito

	vel = vel + accel * t;

	vel = vel * std::pow(DAMPING, t);

	pose.p = pose.p + vel * t;
}

void Particle::integrateVerlet(double t)
{
	const Vector3D posDelta = (2 * pose.p - poset);

	poset = pose.p;

	pose.p = posDelta + accel * t * t;
}