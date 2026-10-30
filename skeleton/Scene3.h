#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <iostream>
#include "gravityForceGenerator.h"
#include "windForceGenerator.h"
#include "MparticleSystem.h"

using namespace std;

class Scene3 : public Scene
{
public:
	explicit Scene3(std::string name) : Scene(std::move(name)) {}

	void init() override {
		// Crear gravedad (predeterminada en todos)
		gravityEarth = new gravityForceGenerator(Vector3D(0.0f, -9.8f, 0.0f));
		
		// Viento: posición (0, 0, 0), radio 30, velocidad (10, 0, 0), k1=1.0, k2=0.0
		windGen = new windForceGenerator(Vector3D(0,0, 0), 30.0f, Vector3D(10.0f, 0.0f, 0.0f), 1.0f, 0.0f);

		generators.push_back(gravityEarth);
		generators.push_back(windGen);

		// Sistema 1: solo gravedad
		ParticleSystem* sys1 = new MparticleSystem(Vector3D(0, 0, 0), Vector3D(-15, 50, 0), 100.0f, 1.0f, gravityEarth);
		systems.push_back(sys1);

		// Sistema 2: gravedad + viento
		ParticleSystem* sys2 = new MparticleSystem(Vector3D(0, 0, 0), Vector3D(0, 50, 0), 100.0f, 1.0f, gravityEarth);
		sys2->addForceGenerator(windGen);  // Agregar viento además de gravedad
		systems.push_back(sys2);

		// Sistema 3: solo gravedad
		ParticleSystem* sys3 = new MparticleSystem(Vector3D(0, 0, 0), Vector3D(15, 50, 0), 100.0f, 20.0f, gravityEarth);
		sys3->addForceGenerator(windGen);  // Agregar viento además de gravedad
		systems.push_back(sys3);
	}

	void update(double dt) override {
		for (forceGenerator* g : generators) {
			g->update(dt);
		}
		for (ParticleSystem* p : systems) {
			p->update(dt);
		}
	}

	void cleanup() override {
		for (forceGenerator* g : generators)
			delete g;
		generators.clear();
		for (ParticleSystem* p : systems) {
			p->cleanup();
			delete p;
		}
		systems.clear();
		gravityEarth = nullptr;
		windGen = nullptr;
	}

private:
	std::vector<forceGenerator*> generators;
	std::vector<ParticleSystem*> systems;
	gravityForceGenerator* gravityEarth = nullptr;
	windForceGenerator* windGen = nullptr;
	float k1 = 1.0f;
	float k2 = 0.0f;
};