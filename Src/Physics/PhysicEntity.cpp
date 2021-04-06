#include "PhysicEntity.h"

namespace BallTrack
{
    PhysicEntity::PhysicEntity(void)
    : Entity()
    {

    }

    PhysicEntity::PhysicEntity(const Model3D& model)
    : Entity(model)
    {

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
}