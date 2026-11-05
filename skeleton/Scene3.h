#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <iostream>
#include "gravityForceGenerator.h"
#include "windForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "MparticleSystem.h"
#include "WhirlwindForceGenerator.h"

using namespace std;

class Scene3 : public Scene
{
public:
	explicit Scene3(std::string name) : Scene(std::move(name)), 
		gravityEarth(nullptr), windGen(nullptr), whirlGen(nullptr), explosionGen(nullptr) {}

	~Scene3() override {
		cleanup();
	}

	void init() override {
		// Crear gravedad (siempre activa)
		gravityEarth = new gravityForceGenerator(Vector3D(0.0f, -9.8f, 0.0f));
		
		// Viento
		windGen = new windForceGenerator(Vector3D(0, 20, 0), 30.0f, Vector3D(30.0f, 0.0f, 0.0f), 2.0f, 0.0f);
		windGen->setEnabled(false);

		// Torbellino
		whirlGen = new WhirlwindForceGenerator(Vector3D(0.0f, 0.0f, 0.0f), 30.0f, 0.5f, 1.0f, 0.0f);
		whirlGen->setEnabled(false);

		// Explosión
		explosionGen = new ExplosionForceGenerator(Vector3D(0, 30, 0), 50.0f, 50000.0f, 0.5f);

		generators.push_back(gravityEarth);
		generators.push_back(windGen);
		generators.push_back(whirlGen);
		generators.push_back(explosionGen);

		// Sistema 1: masa 1.0f, a la izquierda
		ParticleSystem* sys1 = new MparticleSystem(Vector3D(0, -1, 0), Vector3D(-15, 50, 0), 100.0f, 1.0f, gravityEarth);
		sys1->addForceGenerator(windGen);
		sys1->addForceGenerator(whirlGen);
		sys1->addForceGenerator(explosionGen);
		systems.push_back(sys1);

		// Sistema 2: masa 5.0f, a la derecha
		ParticleSystem* sys2 = new MparticleSystem(Vector3D(0, -1, 0), Vector3D(15, 50, 0), 100.0f, 5.0f, gravityEarth);
		sys2->addForceGenerator(windGen);
		sys2->addForceGenerator(whirlGen);
		sys2->addForceGenerator(explosionGen);
		systems.push_back(sys2);
	}

	void keyPress(unsigned char key, const physx::PxTransform& camera) override {
		switch (key) {
		case 'v':  // Activar/desactivar viento
			windGen->toggleEnabled();
			break;
		case 'b':  // Activar/desactivar remolino
			whirlGen->toggleEnabled();
			break;
		case 'n':  // Provocar explosión
			explosionGen->triggerExplosion();
			break;
		}
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
		for (ParticleSystem* p : systems) {
			if (p) {
				p->cleanup();
				delete p;
			}
		}
		systems.clear();

		// Limpiar referencias en generadores antes de borrarlos
		for (forceGenerator* g : generators) {
			if (g) g->clearAllReferences();
		}

		// Luego limpiar generadores
		for (forceGenerator* g : generators) {
			if (g) {
				delete g;
			}
		}
		generators.clear();

		gravityEarth = nullptr;
		windGen = nullptr;
		whirlGen = nullptr;
		explosionGen = nullptr;
	}

private:
	std::vector<forceGenerator*> generators;
	std::vector<ParticleSystem*> systems;
	gravityForceGenerator* gravityEarth;
	windForceGenerator* windGen;
	WhirlwindForceGenerator* whirlGen;
	ExplosionForceGenerator* explosionGen;
};