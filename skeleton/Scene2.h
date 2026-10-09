#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <iostream>
#include "ParticleSystem.h"

using namespace std;

class Scene2 :
    public Scene
{
public:
    explicit Scene2(std::string name) : Scene(std::move(name))
    {}

    void init() override {
        float limit = 10.0f;
        float posvar =  0.1f;
        float velvar = 1.0f;
        float dirvar = 0.05f;
        float lifevar = 1.0f;
        float genvar = 1.0f;
        systems.push_back(new ParticleSystem(Vector3(0,1,0), Vector3(0, 0, 0),limit,
           velvar, dirvar, posvar,lifevar,genvar));
    }

    void update(double dt) override {
        for (ParticleSystem* p : systems) {
            p->update(dt);
        }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        Vector3D shootDir = GetCamera()->getDir().getNormalized();
        float realVel;
        float simVel;
        float mass = 0.f;
        switch (key) {
        case 'c': // Bala de cañon
            realVel = 250.f;
            simVel = 50.f;
            mass = 15.f;
            break;
        case 'v': // Bala de tanque
            realVel = 1800.f;
            simVel = 50.f;
            mass = 40.f;
            break;
        case 'b': // Pistola
            realVel = 330.f;
            simVel = 50.f;
            mass = .1f;
            break;
        }

    }

    void cleanup() override {
        systems.clear();
        for (ParticleSystem* p : systems) {
            p->cleanup();
            delete p;
        }
    }

private:
    std::vector<ParticleSystem*> systems;
};