#ifndef _BALLTRACK_SPHEREENTITY_H
#define _BALLTRACK_SPHEREENTITY_H

#include "Physics/PhysicEntity.h"

namespace BallTrack
{
    struct PhysicOverlap;
    class RectangleEntity;

    class SphereEntity: public PhysicEntity
    {
    public:
        SphereEntity(void);
        SphereEntity(const Model3D& model);

        virtual void update(float dtSeconds) override;

        virtual bool resolveCollision(PhysicEntity* target) override;

        void setRadius(float radius);
        float getRadius(void) const;
        float getMaximumRadius(void) const;

        float distance(const SphereEntity* target);

    protected:
        bool resolveCollision(SphereEntity* target);
        bool resolveCollision(RectangleEntity* target);

    private:
        float m_Radius;
    };
}

#endif //_BALLTRACK_SPHEREENTITY_H