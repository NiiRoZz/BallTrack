#include "Entities/PhysicEntity.h"

namespace BallTrack
{
    PhysicEntity::PhysicEntity(void)
    : Entity()
    , m_Static(false)
    {
    }

    PhysicEntity::PhysicEntity(const Model3D& model, bool _static)
    : Entity(model)
    , m_Static(_static)
    {

    }

    /*void PhysicEntity::render(const TG3D& parentMat)
    {
        TG3D modelMatrix = parentMat * getModelMatrix();

        m_Model3D.render(modelMatrix);

        glBindTexture(GL_TEXTURE_2D, 0);

        for (auto& primitive: m_CollisionPrimitives)
        {
            primitive->render(modelMatrix);
        }
    }*/

    void PhysicEntity::render(const TG3D& parentMat, bool showPrimitives)
    {
        TG3D modelMatrix = parentMat * getModelMatrix();

        m_Model3D.render(modelMatrix);

        if (showPrimitives)
        {
            glBindTexture(GL_TEXTURE_2D, 0);

            for (auto& primitive : m_CollisionPrimitives)
            {
                primitive->render(modelMatrix);
            }
        }
    }

    void PhysicEntity::addCollisionPrimitive(std::unique_ptr<CollisionPrimitive>&& primitive)
    {
        m_CollisionPrimitives.push_back(std::move(primitive));
    }

    void PhysicEntity::update(float dtSeconds)
    {
        if (isStatic()) return;

        static constexpr float GRAVITY = -9.8f;

        // Add Drag to emulate friction
        m_Acceleration = (m_Velocity * -1.f) * 0.95f;

        // Update gravity physics
        m_Velocity += m_Acceleration * dtSeconds;
        m_Velocity.y += GRAVITY * dtSeconds;
        m_Position += m_Velocity * dtSeconds;

        // Clamp velocity near zero
        if (std::abs(m_Velocity.magnitude()) < 0.01f)
        {
            m_Velocity *= 0.f;
        }
    }

    bool PhysicEntity::resolveCollision(PhysicEntity* target)
    {
        bool result = false;

        for (auto& primitive: m_CollisionPrimitives)
        {
            for (auto& primitiveTarget: target->m_CollisionPrimitives)
            {
                result |= primitive->resolveCollision(primitiveTarget.get());
            }
        }
        
        return result;
    }

    const Dir3D& PhysicEntity::getAcceleration() const
    {
        return m_Acceleration;
    }

    const Dir3D& PhysicEntity::getVelocity() const
    {
        return m_Velocity;
    }

    void PhysicEntity::setVelocity(const Dir3D& velocity)
    {
        m_Velocity = velocity;
    }

    float PhysicEntity::getMass() const
    {
        return m_Mass;
    }

    void PhysicEntity::setMass(float mass)
    {
        m_Mass = mass;
    }

    bool PhysicEntity::isStatic() const
    {
        return m_Static;
    }

    void PhysicEntity::setStatic(bool _static)
    {
        m_Static = _static;
    }
}