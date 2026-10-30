#pragma once
#include "ParticleSystem.h"

class forceGenerator;

class FparticleSystem : public ParticleSystem
{
public:
	FparticleSystem(Vector3D Dir, Vector3D Pos, float Limit, float mass = 1.0f, forceGenerator* gen = nullptr);
	void update(double t) override;

protected:
	void createParticle() override;
	void createParticleAtPos(const Vector3D& deathPos);
	Vector3D lastDeathPos;
};