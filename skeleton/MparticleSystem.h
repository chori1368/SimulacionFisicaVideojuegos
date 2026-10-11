#pragma once
#include "ParticleSystem.h"

class MparticleSystem : public ParticleSystem
{
public:
	MparticleSystem(Vector3D Dir, Vector3D Pos, float Limit);
};