#pragma once
#include "forceGenerator.h"

class windForceGenerator : public forceGenerator
{
public:
	// Constructor: posición del volumen, tamaño del volumen, velocidad/dirección del viento
	windForceGenerator(const Vector3D& position, float radius, const Vector3D& windVel, 
		float k1 = 1.0f, float k2 = 0.0f);

	void setWindVelocity(const Vector3D& vel) { windVelocity = vel; }
	Vector3D getWindVelocity() const { return windVelocity; }
	void setCoefficients(float new_k1, float new_k2) { k1 = new_k1; k2 = new_k2; }

protected:
	void applyForce(Particle* particula, double t) override;

private:
	bool isInInfluenceZone(const Vector3D& particlePos) const;

	Vector3D position;    // Centro del volumen de influencia
	float radius;         // Radio de influencia (esfera)
	Vector3D windVelocity;   // Velocidad del viento
	float k1;  // Coeficiente resistencia lineal
	float k2;  // Coeficiente resistencia cuadrática
};

