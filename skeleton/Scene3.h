#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <iostream>
#include "gravityForceGenerator.h"
#include "MparticleSystem.h"

using namespace std;

class Scene3 : public Scene
{
public:
    explicit Scene3(std::string name) : Scene(std::move(name)) {}

    void init() override {
        gravityEarth = new gravityForceGenerator(Vector3D(0.0f, -9.8f, 0.0f));
        gravityLight = new gravityForceGenerator(Vector3D(0.0f, -2.0f, 0.0f));
        generators.push_back(gravityEarth);
        generators.push_back(gravityLight);
        systems.push_back(new MparticleSystem(Vector3(0, 1, 0), Vector3(-10, 0, 0), 100.0f,1,gravityEarth));
        systems.push_back(new MparticleSystem(Vector3(0, 1, 0), Vector3(-5, 0, 0), 100.0f, 10, gravityEarth));
        systems.push_back(new MparticleSystem(Vector3(0, 1, 0), Vector3(0, 0, 0), 100.0f, 1, gravityLight));
        systems.push_back(new MparticleSystem(Vector3(0, 1, 0), Vector3(5, 0, 0), 100.0f, 1));
    }

    void update(double dt) override {
        for (forceGenerator* g : generators)
            g->update(dt);
        for (ParticleSystem* p : systems) {
            p->update(dt);
        }
        for (auto it = particles.begin(); it != particles.end();) {
            Particle* p = *it;
            if (!p) {
                it = particles.erase(it);
                continue;
            }

            p->setlife(p->getlife() - static_cast<float>(dt));
            if (p->getlife() > 0.0f) {
                p->integrate(dt, Integrator::SemiEuler);
                ++it;
            }
            else {
                for (forceGenerator* g : generators) g->removeAfeccted(p);
                delete p;
                it = particles.erase(it);
            }
        }
    }

    void cleanup() override {
        for (Particle* p : particles) 
            delete p;
        particles.clear();

        for (forceGenerator* g : generators)
            delete g;
        generators.clear();
        for (ParticleSystem* p : systems) {
            p->cleanup();
            delete p;
        }
        systems.clear();
        gravityEarth = nullptr;
        gravityLight = nullptr;
    }

private:
    std::vector<Particle*> particles;
    std::vector<forceGenerator*> generators;
    std::vector<ParticleSystem*> systems;
    gravityForceGenerator* gravityEarth = nullptr;
    gravityForceGenerator* gravityLight = nullptr;
};