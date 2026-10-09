#pragma once
#include <random>
#include "Particle.h"

class ParticleSystem
{
public:
	ParticleSystem(Vector3D Dir, Vector3D Pos, float Limit, float velvar, float dirvar, float posvar,
		float lifevar,float genvar);
	void update(double t);
	void cleanup();
protected:
	void createParticle();
	std::vector<Particle*> particles;
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