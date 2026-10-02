#pragma once

#include <vector>
#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Proyectile.h"

using namespace std;

class Scene1 : public Scene {
public:
    explicit Scene1(std::string name) : Scene(std::move(name)) {}

    void init() override {
        m_bulletSpeed = 119;
        m_gravity = Vector3D(0,-6, 0);
        m_mass = 0.005 * pow(1800 / 119, 2);

        m_transform = physx::PxTransform(physx::PxVec3(0,30,0));
        physx::PxShape* target = CreateShape(physx::PxBoxGeometry(10.0f,5.0f,1.0f));
        physx::PxShape* floor = CreateShape(physx::PxBoxGeometry(100.0f,0.2f,100.0f));

        RenderItem* m_renderItem = new RenderItem(target, &m_transform, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
        m_renderItems.push_back(m_renderItem);
        m_transform = physx::PxTransform(0,0,0);

        m_renderItem = new RenderItem(floor, &m_transform, Vector4(0.1f, 0.1f, 0.1f, 1.0f));
        m_renderItems.push_back(m_renderItem);
    }

    void update(double dt) override {
        for (Proyectile* proyectile : m_proyectiles)
            if (proyectile) {
                proyectile->integrate(dt);
            }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'F' || key == 'f') {
            shoot(camera);
        }
        if (key == 'K' || key == 'k') {
            m_bulletSpeed -= 1.0f;
        }
        if (key == 'L' || key == 'l') {
            m_bulletSpeed += 1.0f;
        }
        if (key == 'O' || key == 'o') {
            m_mass -= 1.0f;
        }
        if (key == 'P' || key == 'p') {
            m_mass += 1.0f;
        }
        if (key == 'N' || key == 'n') {
            m_gravity.setY(m_gravity.getY() - 1.0f);
        }
        if (key == 'M' || key == 'm') {
            m_gravity.setY(m_gravity.getY() + 1.0f);
        }
    }

    void cleanup() override {
        for (RenderItem* item : m_renderItems)
            if (item) {
                item->release();
            }
        m_renderItems.clear();

        for (Proyectile* p : m_proyectiles)
            delete p;
        m_proyectiles.clear();
    }

    void shoot(const physx::PxTransform& camera) {
        Vector3D direction = Vector3D(camera.q.rotate(physx::PxVec3(0,0,-1))).normalize();

        Proyectile* proyec = new Proyectile(camera.p,direction * m_bulletSpeed, m_mass ,m_gravity, 0.99,Integrator::SemiEuler);
        m_proyectiles.push_back(proyec);
    }

private:
    vector<Proyectile*> m_proyectiles;
    vector<physx::PxTransform*> transforms;
    physx::PxTransform m_transform;
    float m_bulletSpeed;
    Vector3D m_gravity;
    float m_mass;
    vector<RenderItem*> m_renderItems;
};