#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Vector3D.h"
#include "Particle.h"

class Scene1 : public Scene {
public:
    explicit Scene1(std::string name) : Scene(std::move(name)) {}

    void init() override {
        m_particle = new Particle({ 0,0,0 }, { 2,0,0 });
    }

    void update(double dt) override {
        m_particle->integrate(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    void cleanup() override {
        delete m_particle;
        m_particle = nullptr;
    }

private:
    Particle* m_particle;
};