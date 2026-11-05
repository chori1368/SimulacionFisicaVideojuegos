#pragma once
#include "forceGenerator.h"

class ExplosionForceGenerator : public forceGenerator
{
public:
	// Constructor: centro de explosión, radio, intensidad K, constante de tiempo tau
	ExplosionForceGenerator(const Vector3D& center, float radius, float K, float tau);

	void setCenter(const Vector3D& c) { center = c; }
	Vector3D getCenter() const { return center; }

	void triggerExplosion();  // Inicia la explosión
	bool isActive() const;    // Comprueba si la explosión sigue activa (t < 4*tau)
	double getElapsedTime() const;
	void update(double t) override;

private:
	Vector3D center;      // Centro de la explosión (xc, yc, zc)
	float radius;         // Radio de influencia R
	float K;              // Intensidad de la explosión
	float tau;            // Constante de tiempo de la explosión
	double explosionTime; // Tiempo de inicio de la explosión (-1 si no activa)

	void applyForce(Particle* particula, double t) override;
};

