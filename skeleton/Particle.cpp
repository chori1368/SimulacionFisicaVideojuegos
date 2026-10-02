#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D _vel,Vector3D xlr8, float dumping,Integrator newIntegrator) {
	pose = physx::PxTransform(pos);
	poset = physx::PxTransform(0,0,0);
	vel = _vel;
	accel = xlr8;
	damping = dumping;
	physx::PxShape* sphere = CreateShape(physx::PxSphereGeometry(1.0f));
	renderItem = new RenderItem(sphere, &pose, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	integrator = newIntegrator;
}
Particle::~Particle() {
	renderItem->release();
}

void Particle::integrate(double t) {
	// Euler
	switch (integrator) {
		case (Integrator::Euler):
		{
			integrateEuler(t);
		}
		case (Integrator::SemiEuler):
		{
			integrateSemiEuler(t);
		}
		case (Integrator::Verlet):
		{
			if (!poset.p.isZero()) integrateVerlet(t);

			else
			{
				poset = pose;
				integrateSemiEuler(t);
			}
		}
	}
}

void Particle::integrateEuler(double t) {
	pose.p += vel * t;
	vel += accel * t;
	vel = vel * pow(damping, t);
}
void Particle::integrateSemiEuler(double t) {
	vel += accel * t;
	pose.p += vel * t;
	vel = vel * pow(damping, t);
}
void Particle::integrateVerlet(double t) {
	physx::PxTransform currPos = pose;

	pose.p = 2 * pose.p - poset.p + physx::PxTransform(accel * pow(t, 2)).p;
	pose = currPos;
}