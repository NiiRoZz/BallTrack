#include "RectangleEntity.h"
#include "SphereEntity.h"

#include <cassert>
#include <cmath>

namespace BallTrack
{
    RectangleEntity::RectangleEntity(void)
    : PhysicEntity()
    {

    }

    RectangleEntity::RectangleEntity(const Model3D& model)
    : PhysicEntity(model)
    {

    }

    bool RectangleEntity::resolveCollision(PhysicEntity* target)
    {
        SphereEntity* sphereEntity = dynamic_cast<SphereEntity*>(target);
        if (sphereEntity != nullptr)
        {
            return sphereEntity->resolveCollision((PhysicEntity*) this);
        }
        
        assert(false && "resolveCollision function of RectangleEntity can't handle the target type entity\n");
        return false;
    }

    void RectangleEntity::update(float dtSeconds)
    {
        (void) dtSeconds;
    }

    const Vector3& RectangleEntity::getSize(void) const
    {
        return m_Size;
    }

    Vector3 RectangleEntity::getScaledSize(void) const
    {
        return Vector3(m_Size.x * m_Scale.mat[0][0], m_Size.y * m_Scale.mat[1][1], m_Size.z * m_Scale.mat[2][2]);
    }

    void RectangleEntity::setSize(Vector3 size)
    {
        m_Size = std::move(size);
    }
}