#pragma once
#include "windForceGenerator.h"

class WhirlwindForceGenerator : public windForceGenerator
{
public:
	// Constructor: posición del centro del torbellino, radio de influencia, constante K, k1, k2
	WhirlwindForceGenerator(const Vector3D& center, float radius, float K, 
		float k1 = 1.0f, float k2 = 0.0f);

	void setK(float newK) { K = newK; }
	float getK() const { return K; }

protected:
	void applyForce(Particle* particula, double t) override;

private:
	Vector3D calculateWhirlwindVelocity(const Vector3D& particlePos) const;

	Vector3D center;   // Centro del torbellino (xc, yc, zc)
	float K;           // Constante proporcional a la fuerza del torbellino
};

