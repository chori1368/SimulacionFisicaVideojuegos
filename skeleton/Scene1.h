#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Vector3D.h"

class Scene1 : public Scene {
public:
    explicit Scene1(std::string name) : Scene(std::move(name)) {}

    void init() override {
        Vector3D u(3,1,0);
        Vector3D v(0,4,0);
        Vector3D w = u.cross(v);
        u.normalizethis();
        v.normalizethis();
        w.normalizethis();

        physx::PxShape* shapex = CreateShape(physx::PxSphereGeometry(1.0f));
        m_transform1 = physx::PxTransform(u*5);

        // Se registra el RenderItem exactamente como en la plantilla original
        m_renderItem1 = new RenderItem(shapex, &m_transform1, Vector4(1.0f, 0.0f, 0.0f, 1.0f));

        physx::PxShape* shapey = CreateShape(physx::PxSphereGeometry(1.0f));
        m_transform2 = physx::PxTransform(v*5);

        // Se registra el RenderItem exactamente como en la plantilla original
        m_renderItem2 = new RenderItem(shapey, &m_transform2, Vector4(0.0f, 1.0f, 0.0f, 1.0f));

        physx::PxShape* shapez = CreateShape(physx::PxSphereGeometry(1.0f));
        m_transform3 = physx::PxTransform(w*5);

        // Se registra el RenderItem exactamente como en la plantilla original
        m_renderItem3 = new RenderItem(shapey, &m_transform3, Vector4(0.0f, 0.0f, 1.0f, 1.0f));
    }

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'r' || key == 'R') {
            m_transform.p = physx::PxVec3(0.0f, 10.0f, 0.0f); // Reset
        }
    }

    void cleanup() override {
        if (m_renderItem1) {
            m_renderItem1->release(); // Deregistra y destruye el item
            m_renderItem1 = nullptr;
        }
        if (m_renderItem2) {
            m_renderItem2->release(); // Deregistra y destruye el item
            m_renderItem2 = nullptr;
        }
        if (m_renderItem3) {
            m_renderItem3->release(); // Deregistra y destruye el item
            m_renderItem3 = nullptr;
        }
    }

private:
    physx::PxTransform m_transform;
    physx::PxTransform m_transform1;
    physx::PxTransform m_transform2;
    physx::PxTransform m_transform3;
    RenderItem* m_renderItem1{ nullptr };
    RenderItem* m_renderItem2{ nullptr };
    RenderItem* m_renderItem3{ nullptr };
};