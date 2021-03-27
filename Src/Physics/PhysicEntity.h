#ifndef _BALLTRACK_PHYSICENTITY_H
#define _BALLTRACK_PHYSICENTITY_H

#include "Entities/Entity.h"
#include "Math/Vector3.h"
#include "Math/Pos3D.h"

namespace BallTrack
{
    class PhysicEntity: public Entity
    {
    public:
        PhysicEntity(void);
        PhysicEntity(const Model3D& model);

        const Vector3& getAcceleration() const;
        const Vector3& getVelocity() const;
        float getMass() const;

    protected:
        Vector3 m_Acceleration;
        Vector3 m_Velocity;
        float m_Mass;
    };
}

#endif //_BALLTRACK_PHYSICENTITY_H