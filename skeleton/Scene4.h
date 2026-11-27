#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <iostream>
#include "gravityForceGenerator.h"
#include "windForceGenerator.h"
#include "SpringForceGenerator.h"
#include "ElasticBandForceGenerator.h"
#include "Particle.h"

using namespace std;

class Scene4 : public Scene
{
public:
	explicit Scene4(std::string name) : Scene(std::move(name)), 
		k(10.0f), currentIntegrator(Integrator::SemiEuler),
		gravityEnabled(false), windEnabled(false)
	{}

	~Scene4() override {
		cleanup();
	}

	void init() override {
		// generadores
		gravityGen = new gravityForceGenerator(Vector3D(0.0f, -9.8f, 0.0f));
		gravityGen->setEnabled(false);
		windGen = new windForceGenerator(Vector3D(0, 20, 0), 30.0f, Vector3D(-30.0f, 0.0f, 0.0f), 1.0f, 0.0f);
		windGen->setEnabled(false);

		// particula a un anchor
		Vector3D anchorPoint1(0.0f, 25.0f, 0.0f);
		anchorParticle1 = new Particle(anchorPoint1, Vector3D(0.0f, 0.0f, 0.0f), 
									   Vector3D(0.0f, 0.0f, 0.0f), 1.0f, 5000.0f);
		
		particle1 = new Particle(
			Vector3D(0.0f, 20.0f, 0.0f),
			Vector3D(0.0f, 0.0f, 0.0f),
			Vector3D(0.0f, 0.0f, 0.0f),
			1.0f, 5000.0f
		);

		springGen1 = new SpringForceGenerator(k, 5.0f, anchorParticle1);
		springGen1->addAfeccted(particle1);

		anchorRender1 = new RenderItem(
			CreateShape(physx::PxBoxGeometry(0.5f, 0.5f, 0.5f), nullptr),
			new physx::PxTransform(anchorPoint1),
			Vector4(0.0f, 1.0f, 0.0f, 1.0f)
		);

		// dos particulas entre si
		particle2a = new Particle(
			Vector3D(-8.0f, 15.0f, 0.0f),
			Vector3D(0.0f, 0.0f, 0.0f),
			Vector3D(0.0f, 0.0f, 0.0f),
			1.0f, 5000.0f
		);

		particle2b = new Particle(
			Vector3D(-2.0f, 15.0f, 0.0f),
			Vector3D(0.0f, 0.0f, 0.0f),
			Vector3D(0.0f, 0.0f, 0.0f),
			1.0f, 5000.0f
		);

		springGen21 = new SpringForceGenerator(k, 6.0f, particle2b);
		springGen21->addAfeccted(particle2a);
		springGen22 = new SpringForceGenerator(k, 6.0f, particle2a);
		springGen22->addAfeccted(particle2b);

		//  dos particulas con banda elastica
		particle3a = new Particle(
			Vector3D(2.0f, 15.0f, 0.0f),
			Vector3D(0.0f, 0.0f, 0.0f),
			Vector3D(0.0f, 0.0f, 0.0f),
			1.0f, 5000.0f
		);

		particle3b = new Particle(
			Vector3D(8.0f, 15.0f, 0.0f),
			Vector3D(0.0f, 0.0f, 0.0f),
			Vector3D(0.0f, 0.0f, 0.0f),
			1.0f, 5000.0f
		);

		elasticGen1 = new ElasticBandForceGenerator(k, 6.0f, particle3b);
		elasticGen1->addAfeccted(particle3a);
		elasticGen2 = new ElasticBandForceGenerator(k, 6.0f, particle3a);
		elasticGen2->addAfeccted(particle3b);






		// añadir particulas a generadores
		vector<Particle*> allParticles = { particle2a, particle3a };
		for (Particle* p : allParticles) {
			windGen->addAfeccted(p);
		}
		allParticles = { particle1 };
		for (Particle* p : allParticles) {
			gravityGen->addAfeccted(p);
		}
	}

	void keyPress(unsigned char key, const physx::PxTransform& camera) override {
		switch (key) {
		case 'k':  // Aumentar k
			k += 10.0f;
			springGen1->setK(k);
			springGen21->setK(k);
			springGen22->setK(k);
			elasticGen1->setK(k);
			elasticGen2->setK(k);
			cout << "k = " << k << endl;
			break;

		case 'l':  // Disminuir k
			k = max(1.0f, k - 10.0f);
			springGen1->setK(k);
			springGen21->setK(k);
			springGen22->setK(k);
			elasticGen1->setK(k);
			elasticGen2->setK(k);
			cout << "k = " << k << endl;
			break;

		case 'n':  // Euler explícito
			currentIntegrator = Integrator::Euler;
			cout << "Integrador: Euler" << endl;
			break;

		case 'b':  // Euler semi-implícito
			currentIntegrator = Integrator::SemiEuler;
			cout << "Integrador: SemiEuler" << endl;
			break;

		case 'v':  // Verlet
			currentIntegrator = Integrator::Verlet;
			cout << "Integrador: Verlet" << endl;
			break;

		case 'r':  // Reiniciar escena
			cleanup();
			init();
			cout << "Escena reiniciada" << endl;
			break;

		case 'g':  // Activar/desactivar gravedad
			gravityEnabled = !gravityEnabled;
			gravityGen->setEnabled(gravityEnabled);
			cout << "Gravedad: " << (gravityEnabled ? "ON" : "OFF") << endl;
			break;

		case 'h':  // Activar/desactivar viento
			windEnabled = !windEnabled;
			windGen->setEnabled(windEnabled);
			cout << "Viento: " << (windEnabled ? "ON" : "OFF") << endl;
			break;
		}
	}

	void update(double dt) override {
		gravityGen->update(dt);
		windGen->update(dt);
		springGen1->update(dt);
		springGen21->update(dt);
		springGen22->update(dt);
		elasticGen1->update(dt);
		elasticGen2->update(dt);

		// Integrar todas las partículas (excepto anclajes)
		particle1->integrate(dt, currentIntegrator);
		particle2a->integrate(dt, currentIntegrator);
		particle2b->integrate(dt, currentIntegrator);
		particle3a->integrate(dt, currentIntegrator);
		particle3b->integrate(dt, currentIntegrator);
	}

	void cleanup() override {
		// Limpiar partículas
		if (particle1) delete particle1;
		if (particle2a) delete particle2a;
		if (particle2b) delete particle2b;
		if (particle3a) delete particle3a;
		if (particle3b) delete particle3b;
		if (anchorParticle1) delete anchorParticle1;

		// Limpiar generadores
		if (gravityGen) {
			gravityGen->clearAllReferences();
			delete gravityGen;
		}
		if (windGen) {
			windGen->clearAllReferences();
			delete windGen;
		}
		if (springGen1) {
			springGen1->clearAllReferences();
			delete springGen1;
		}
		if (springGen21) {
			springGen21->clearAllReferences();
			delete springGen21;
		}
		if (springGen22) {
			springGen22->clearAllReferences();
			delete springGen22;
		}
		if (elasticGen1) {
			elasticGen1->clearAllReferences();
			delete elasticGen1;
		}
		if (elasticGen2) {
			elasticGen2->clearAllReferences();
			delete elasticGen2;
		}
		if (anchorRender1) {
			anchorRender1->release();
		}

		// Reinicializar punteros
		particle1 = nullptr;
		particle2a = nullptr;
		particle2b = nullptr;
		particle3a = nullptr;
		particle3b = nullptr;
		anchorParticle1 = nullptr;
		gravityGen = nullptr;
		windGen = nullptr;
		springGen1 = nullptr;
		springGen21 = nullptr;
		springGen22 = nullptr;
		elasticGen1 = nullptr;
		elasticGen2 = nullptr;
		anchorRender1 = nullptr;
	}

private:
	// Partículas
	Particle* particle1 = nullptr;
	Particle* anchorParticle1 = nullptr;
	Particle* particle2a = nullptr;
	Particle* particle2b = nullptr;
	Particle* particle3a = nullptr;
	Particle* particle3b = nullptr;

	// Generadores de fuerzas
	gravityForceGenerator* gravityGen = nullptr;
	windForceGenerator* windGen = nullptr;
	SpringForceGenerator* springGen1 = nullptr;
	SpringForceGenerator* springGen21 = nullptr;
	SpringForceGenerator* springGen22 = nullptr;
	ElasticBandForceGenerator* elasticGen1 = nullptr;
	ElasticBandForceGenerator* elasticGen2 = nullptr;

	// Visualización
	RenderItem* anchorRender1 = nullptr;

	// Parámetros
	float k;
	Integrator currentIntegrator;
	bool gravityEnabled;
	bool windEnabled;
};

