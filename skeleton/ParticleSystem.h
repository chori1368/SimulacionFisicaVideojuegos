#pragma once
#include <random>
#include "Particle.h"

class ParticleSystem
{
public:
	ParticleSystem(Vector3D Dir, Vector3D Pos, float Limit);
	virtual void update(double t);
	void cleanup();
protected:
	virtual void createParticle();
	bool isWithinLimit(const Vector3D& particlePos);
	std::vector<Particle*> particles;
	int maxParticles;
	float limit;
	Vector3D pos;
	Vector3D dir;
	std::default_random_engine generator;
	std::normal_distribution<float> pos_dist;
	std::normal_distribution<float> speed_dist;
	std::normal_distribution<float> dir_dist;
	std::normal_distribution<float> lifetime_dist;

	std::normal_distribution<float> part_gen_dist;
};