#include "CircleEntity.h"

namespace BallTrack
{
    CircleEntity::CircleEntity(void)
    : PhysicEntity()
    {

    }

    CircleEntity::CircleEntity(const Model3D& model)
    : PhysicEntity(model)
    {

    }

    void CircleEntity::setRadius(float radius)
    {
        m_Radius = radius;
    }

    float CircleEntity::getRadius(void) const
    {
        return m_Radius;
    }
}