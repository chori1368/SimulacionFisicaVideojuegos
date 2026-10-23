#pragma once
#include "forceGenerator.h"

class gravityForceGenerator final : public forceGenerator
{
public:
	gravityForceGenerator(const Vector3D& gravityAccel);

protected:
	void applyForce(Particle* particula, double t) override;

private:
	Vector3D gravity; // aceleración gravitatoria
};