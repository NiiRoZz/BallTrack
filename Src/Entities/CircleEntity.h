#ifndef _BALLTRACK_CIRCLEENTITY_H
#define _BALLTRACK_CIRCLEENTITY_H

#include "Physics/PhysicEntity.h"

namespace BallTrack
{
    class CircleEntity: public PhysicEntity
    {
    public:
        CircleEntity(void);
        CircleEntity(const Model3D& model);

        virtual void update(float dtSeconds);

        void setRadius(float radius);
        float getRadius(void) const;

    private:
        float m_Radius;
    };
}

#endif //_BALLTRACK_CIRCLEENTITY_H