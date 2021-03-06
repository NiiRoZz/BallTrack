#ifndef _BALLTRACK_SPHERECOLLISIONPRIMITIVE_H
#define _BALLTRACK_SPHERECOLLISIONPRIMITIVE_H

#if defined(WIN32) || defined(WIN64)
#define NOMINMAX
#define _USE_MATH_DEFINES

#endif


#include <cmath>
#include "Physics/CollisionPrimitive.h"

namespace BallTrack
{
    class RectangleCollisionPrimitive;

    class SphereCollisionPrimitive: public CollisionPrimitive
    {
    public:
        SphereCollisionPrimitive(PhysicEntity* parent);

        virtual void render(const TG3D& parentMat = TG3D()) override;

        virtual bool resolveCollision(CollisionPrimitive* target) override;

        virtual TG3D getModelMatrix() const;

        void setRadius(float radius);
        float getRadius() const;
        float getMaximumRadius() const;

        float distance(const SphereCollisionPrimitive* target);

    protected:
        bool resolveCollision(SphereCollisionPrimitive* target);
        bool resolveCollision(RectangleCollisionPrimitive* target);

    protected:
        float m_Radius;
    };
}

#endif //_BALLTRACK_SPHERECOLLISIONPRIMITIVE_H