#pragma once
#include <random>
#include <vector>
#include "Particle.h"

class forceGenerator;

class ParticleSystem
{
public:
	ParticleSystem(Vector3D Dir, Vector3D Pos, float Limit, float mass = 1.0f, forceGenerator* gravityGen = nullptr);
	virtual ~ParticleSystem() = default;

	virtual void update(double t);
	void cleanup();

	// Agregar más generadores de fuerza
	void addForceGenerator(forceGenerator* gen);
	void removeForceGenerator(forceGenerator* gen);

protected:
	virtual void createParticle();
	bool isWithinLimit(const Vector3D& particlePos);

	std::vector<Particle*> particles;
	std::vector<forceGenerator*> generators;  // NUEVO: lista de generadores
	forceGenerator* gravityGen;               // Generador de gravedad predeterminado

	int maxParticles;
	float limit;
	Vector3D pos;
	Vector3D dir;
	float masa;
	std::default_random_engine generator;
	std::normal_distribution<float> pos_dist;
	std::normal_distribution<float> speed_dist;
	std::normal_distribution<float> dir_dist;
	std::normal_distribution<float> lifetime_dist;
	std::normal_distribution<float> part_gen_dist;
};