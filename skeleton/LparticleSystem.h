#pragma once
#include "ParticleSystem.h"

class LparticleSystem : public ParticleSystem
{
public:
	LparticleSystem(Vector3D Dir, Vector3D Pos, float Limit, float Masa, forceGenerator* fg);
protected:
	void createParticle() override;
};