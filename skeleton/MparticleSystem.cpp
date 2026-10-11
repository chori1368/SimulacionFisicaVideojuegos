#include "MparticleSystem.h"

MparticleSystem::MparticleSystem(Vector3D Dir, Vector3D Pos, float Limit) :
	ParticleSystem(Dir,Pos,Limit) {

	pos_dist = std::normal_distribution<float>(0.0f, 0.1f);
	speed_dist = std::normal_distribution<float>(30.0f, 1.0f);
	dir_dist = std::normal_distribution<float>(0.0f, 0.05);
	lifetime_dist = std::normal_distribution<float>(6.0f, 1.0f);

	part_gen_dist = std::normal_distribution<float>(2, 1.0);
	maxParticles = 5000;
}