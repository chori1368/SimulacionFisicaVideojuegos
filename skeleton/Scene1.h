#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <iostream>
#include "Proyectile.h"

using namespace std;

class Scene1 :
    public Scene
{
public:
    explicit Scene1(std::string name) : Scene(std::move(name))
    {}

    void init() override {
        m_transform = physx::PxTransform(physx::PxVec3(0, 30, 0));
        physx::PxShape* target = CreateShape(physx::PxBoxGeometry(10.0f, 5.0f, 1.0f));
        physx::PxShape* floor = CreateShape(physx::PxBoxGeometry(100.0f, 0.2f, 100.0f));

        RenderItem* m_renderItem = new RenderItem(target, &m_transform, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
        m_renderItems.push_back(m_renderItem);
        m_transform = physx::PxTransform(0, 0, 0);

        m_renderItem = new RenderItem(floor, &m_transform, Vector4(0.1f, 0.1f, 0.1f, 1.0f));
        m_renderItems.push_back(m_renderItem);
    }

    void update(double dt) override {
        for (Proyectile* p : particles) {
            p->integrate(dt, Integrator::SemiEuler);
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
            particles.push_back(new Proyectile(camera.p, shootDir, realVel + offsetVelocidad, simVel, mass + offsetMasa));
            break;
        case 'v': // Bala de tanque
            realVel = 1800.f;
            simVel = 50.f;
            mass = 40.f;
            particles.push_back(new Proyectile(camera.p, shootDir, realVel + offsetVelocidad, simVel, mass + offsetMasa));
            break;
        case 'b': // Pistola
            realVel = 330.f;
            simVel = 50.f;
            mass = .1f;
            particles.push_back(new Proyectile(camera.p, shootDir, realVel + offsetVelocidad, simVel, mass + offsetMasa));
            break;

        case 'y':
            offsetMasa += 10.f;
            std::cout << "Offset Masa: " << offsetMasa << '\n';
            break;
        case 'h':
            offsetMasa -= 10.f;
            std::cout << "Offset Masa: " << offsetMasa << '\n';
            break;
        case 'u':
            offsetVelocidad += 10.f;
            std::cout << "Offset Vel: " << offsetVelocidad << '\n';
            break;
        case 'j':
            offsetVelocidad -= 10.f;
            std::cout << "Offset Vel: " << offsetVelocidad << '\n';
            break;
        }

    }

    void cleanup() override {
        for (RenderItem* item : m_renderItems)
            if (item) {
                item->release();
            }
        m_renderItems.clear();
        for (Proyectile* p : particles) {
            delete p;
        }
    }

private:
    std::vector<Proyectile*> particles;
    physx::PxTransform m_transform;
    vector<RenderItem*> m_renderItems;

    float offsetMasa = 0.f;
    float offsetVelocidad = 0.f;

};