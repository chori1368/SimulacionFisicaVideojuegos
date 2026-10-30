#pragma once
#include "ParticleSystem.h"

class forceGenerator;

class LparticleSystem : public ParticleSystem
{
public:
	LparticleSystem(Vector3D Dir, Vector3D Pos, float Limit, float mass = 1.0f, forceGenerator* gen = nullptr);

protected:
	void createParticle() override;
};