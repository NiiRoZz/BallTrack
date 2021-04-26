#include "CollisionPrimitive.h"

#include "Physics/SphereCollisionPrimitive.h"
#include "Physics/RectangleCollisionPrimitive.h"
#include "Math/Vector3.h"

namespace BallTrack
{
    std::unique_ptr<CollisionPrimitive> CollisionPrimitive::CreateSphere(Entity* parent, const Pos3D& pos, const Rt3D& rt, float radius)
    {
        auto result = std::make_unique<SphereCollisionPrimitive>(parent);
        result->setPosition(pos);
        result->setRotation(rt);
        result->setRadius(radius);

        return result;
    }

    std::unique_ptr<CollisionPrimitive> CollisionPrimitive::CreateRectangle(Entity* parent, const Pos3D& pos, const Rt3D& rt, const Vector3& size)
    {
        auto result = std::make_unique<RectangleCollisionPrimitive>(parent);
        result->setRotation(rt);
        result->setPosition(pos);
        result->setSize(size);

        return result;
    }

    CollisionPrimitive::CollisionPrimitive(Entity* parent)
    : m_Parent(parent)
    {
    }

    Sc3D CollisionPrimitive::getScale() const
    {
        return m_Parent->getScale();
    }

    Rt3D CollisionPrimitive::getRotation() const
    {
        return m_Parent->getRotation() * m_Rotation;
    }

    void CollisionPrimitive::setRotation(const Rt3D& rotation)
    {
        m_Rotation = rotation;
    }

    Pos3D CollisionPrimitive::getPosition() const
    {
        return m_Position * m_Parent->getModelMatrix();
    }

    void CollisionPrimitive::setPosition(const Pos3D& pos)
    {
        m_Position = pos;
    }

    Entity* CollisionPrimitive::getParent() const
    {
        return m_Parent;
    }

    TG3D CollisionPrimitive::getModelMatrix() const
    {
        return Tr3D(m_Position) * m_Rotation * Sc3D(1.f);
    }

    Pos3D CollisionPrimitive::getOffsetFromParent() const
    {
        return m_Position;
    }
}