#ifndef _BALLTRACK_SPHEREENTITY_H
#define _BALLTRACK_SPHEREENTITY_H

#include "Physics/PhysicEntity.h"

namespace BallTrack
{
    class SphereEntity: public PhysicEntity
    {
    public:
        SphereEntity(void);
        SphereEntity(const Model3D& model);

        virtual void update(float dtSeconds);

        void setRadius(float radius);
        float getRadius(void) const;

    private:
        float m_Radius;
    };
}

#endif //_BALLTRACK_SPHEREENTITY_H