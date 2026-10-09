#include "Proyectile.h"

Proyectile::Proyectile(const Vector3D& Pos, Vector3D& dir, float realVel, float simVel, float mass)
    : Particle(Pos,0, 0, mass,0)
{
    simMass = (mass * realVel * realVel) / (simVel * simVel);
    simGravity = GRAVITY * ((simVel * simVel) / (realVel * realVel));

    vel = dir * simVel;
}

void Proyectile::integrateSemiEuler(double t)
{
    // Apply gravity
    accel += Vector3D(0.f, simGravity, 0.f);

    Particle::integrateSemiEuler(t);
}