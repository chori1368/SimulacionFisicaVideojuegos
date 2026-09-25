#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D _vel,Vector3D xlr8, float dumping,Integrator newIntegrator) {
	pose = physx::PxTransform(pos);
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
			integrateVerlet(t);
		}
	}
}

void Particle::integrateEuler(double t) {
	pose.p.x += vel.getX() * t;
	pose.p.y += vel.getY() * t;
	pose.p.z += vel.getZ() * t;
	vel += accel * t;
	vel = vel * pow(damping,t);
}
void Particle::integrateSemiEuler(double t) {
	vel += accel * t;
	pose.p.x += vel.getX() * t;
	pose.p.y += vel.getY() * t;
	pose.p.z += vel.getZ() * t;
	vel = vel * pow(damping,t);
}
void Particle::integrateVerlet(double t) {
	if (poset.p.x != 0 && poset.p.y != 0 && poset.p.z != 0) {
		poset.p.x += vel.getX() * t;
		poset.p.y += vel.getY() * t;
		poset.p.z += vel.getZ() * t;
		vel += accel * t;
		vel = vel * pow(damping, t);
	}
	else {
		//pose.p.x = 2*
	}
}