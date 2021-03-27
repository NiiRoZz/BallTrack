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

    const Vector3& PhysicEntity::getAcceleration() const
    {
        return m_Acceleration;
    }

    const Vector3& PhysicEntity::getVelocity() const
    {
        return m_Velocity;
    }

    float PhysicEntity::getMass() const
    {
        return m_Mass;
    }
}