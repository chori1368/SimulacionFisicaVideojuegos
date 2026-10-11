#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <iostream>
#include "MparticleSystem.h"
#include "LparticleSystem.h"
#include "FparticleSystem.h"

using namespace std;

class Scene2 :
    public Scene
{
public:
    explicit Scene2(std::string name) : Scene(std::move(name))
    {}

    void init() override {
    }

    void update(double dt) override {
        for (ParticleSystem* p : systems) {
            p->update(dt);
        }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        switch (key) {
        case 'c': // Mangera
            systems.push_back(new MparticleSystem(Vector3(1, 0, 0), Vector3(0, 0, 0), 100.0f));
            break;
        case 'v': // lluvia
            systems.push_back(new LparticleSystem(Vector3(0, -1, 0), Vector3(0, 40, 0), 100.0f));
            break;
        case 'b': // fuego artificial
            systems.push_back(new FparticleSystem(Vector3(0, 1, 0), Vector3(0, 0, 0), 0.0f));
            break;
        case 'r': // eliminar fuente
            cleanup();
            break;
        }

    }

    void cleanup() override {
        for (ParticleSystem* p : systems) {
            p->cleanup();
            delete p;
        }
        systems.clear();
    }

private:
    std::vector<ParticleSystem*> systems;
};