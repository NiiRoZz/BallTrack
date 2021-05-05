#ifndef _BALLTRACK_RECTANGLECOLLISIONPRIMITIVE_H
#define _BALLTRACK_RECTANGLECOLLISIONPRIMITIVE_H

#include "Physics/CollisionPrimitive.h"
#include "Math/Vector3.h"

namespace BallTrack
{
    class RectangleCollisionPrimitive: public CollisionPrimitive
    {
    public:
        RectangleCollisionPrimitive(Entity* parent);

        virtual void render(const TG3D& parentMat = TG3D()) override;

        virtual bool resolveCollision(CollisionPrimitive* target) override;
        virtual void dynamicCollision(CollisionPrimitive* target) override;

        virtual TG3D getModelMatrix() const;

        const Vector3& getSize(void) const;
        Vector3 getScaledSize(void) const;
        void setSize(const Vector3& size);

    protected:
        Vector3 m_Size;
    };
}

#endif //_BALLTRACK_RECTANGLECOLLISIONPRIMITIVE_H