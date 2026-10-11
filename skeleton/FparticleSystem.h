#pragma once
#include "ParticleSystem.h"

class FparticleSystem : public ParticleSystem
{
public:
	FparticleSystem(Vector3D Dir, Vector3D Pos, float Limit);
	void update(double t) override;
protected:
	void createParticle() override;
	void createParticleAtPos(const Vector3D& deathPos);
	Vector3D lastDeathPos;
};