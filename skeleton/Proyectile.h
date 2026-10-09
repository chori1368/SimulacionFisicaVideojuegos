#pragma once
#include "particle.h"
constexpr float GRAVITY = -9.81f;

class Proyectile : public Particle
{
public:
    Proyectile(const Vector3D& Pos, Vector3D& dir, float realVel, float simVel, float mass);

private:
    virtual void integrateSemiEuler(double t) override;
    float simMass;
    float simGravity;
};

