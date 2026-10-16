#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <iostream>
#include "forceGenerator.h"

using namespace std;

class Scene3 :
    public Scene
{
public:
    explicit Scene3(std::string name) : Scene(std::move(name))
    {}

    void init() override {
    }

    void update(double dt) override {
        for (forceGenerator* g : generators) {
            g->update(dt);
        }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        switch (key) {
        }

    }

    void cleanup() override {
        for (Particle* p : particles) {
            delete p;
        }
        particles.clear();
        for (forceGenerator* g : generators) {
            delete g;
        }
        generators.clear();
    }

private:
    std::vector<Particle*> particles;
    std::vector<forceGenerator*> generators;
};