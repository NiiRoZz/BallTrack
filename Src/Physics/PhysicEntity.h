#ifndef _BALLTRACK_PHYSICENTITY_H
#define _BALLTRACK_PHYSICENTITY_H

#include "Entities/Entity.h"
#include "Math/Vector3.h"
#include "Math/Pos3D.h"
#include "Math/Dir3D.h"

namespace BallTrack
{
    class PhysicEntity: public Entity
    {
    public:
        PhysicEntity(void);
        PhysicEntity(const Model3D& model);

        virtual void update(float dtSeconds) = 0;

        virtual bool resolveCollision(PhysicEntity* target) = 0;

        const Dir3D& getAcceleration() const;
        const Dir3D& getVelocity() const;
        float getMass() const;

    protected:
        Dir3D m_Acceleration;
        Dir3D m_Velocity;
        float m_Mass;
    };
}

#endif //_BALLTRACK_PHYSICENTITY_H