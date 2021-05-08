#ifndef _BALLTRACK_COLLISIONPRIMITIVE_H
#define _BALLTRACK_COLLISIONPRIMITIVE_H

#include <memory>

#include "Entities/Entity.h"

#include "Math/Pos3D.h"
#include "Math/Sc3D.h"
#include "Math/Rt3D.h"
#include "Math/Vector3.h"

namespace BallTrack
{
    class PhysicEntity;

    class CollisionPrimitive: public Drawable
    {
    public:
        static std::unique_ptr<CollisionPrimitive> CreateSphere(PhysicEntity* parent, const Pos3D& pos, const Rt3D& rt, float radius);
        static std::unique_ptr<CollisionPrimitive> CreateRectangle(PhysicEntity* parent, const Pos3D& pos, const Rt3D& rt, const Vector3& size);

    public:
        CollisionPrimitive(PhysicEntity* parent);

        Sc3D getScale() const;

        Rt3D getRotation() const;
        void setRotation(const Rt3D& rotation);

        Pos3D getPosition() const;
        void setPosition(const Pos3D& pos);

        PhysicEntity* getParent() const;

        virtual TG3D getModelMatrix() const;

        Pos3D getOffsetFromParent() const;

        virtual bool resolveCollision(CollisionPrimitive* target) = 0;

    protected:
        PhysicEntity* m_Parent;

        Pos3D m_Position;
        Rt3D m_Rotation;
    };
}

#endif //_BALLTRACK_COLLISIONPRIMITIVE_H