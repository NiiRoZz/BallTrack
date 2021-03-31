#include "SphereEntity.h"
#include "RectangleEntity.h"

#include <cassert>
#include <cmath>

namespace BallTrack
{
    SphereEntity::SphereEntity(void)
    : PhysicEntity()
    {

    }

    SphereEntity::SphereEntity(const Model3D& model)
    : PhysicEntity(model)
    {

    }

    void SphereEntity::update(float dtSeconds)
    {
        static constexpr float GRAVITY = -0.9f;

        // Add Drag to emulate rolling friction
        m_Acceleration = (m_Velocity * -1.f) * 0.8f;

        // Update ball physics
        m_Velocity += m_Acceleration * dtSeconds;
        m_Velocity.y += m_Acceleration.y * dtSeconds + GRAVITY * dtSeconds;

        m_Position += m_Velocity * dtSeconds;

        // Clamp velocity near zero
        if (std::abs(m_Velocity.magnitude()) < 0.01f)
        {
            m_Velocity *= 0.f;
        }
    }

    bool SphereEntity::resolveCollision(PhysicEntity* target)
    {
        SphereEntity* sphereEntity = dynamic_cast<SphereEntity*>(target);
        if (sphereEntity != nullptr)
        {
            return resolveCollision(sphereEntity);
        }

        RectangleEntity* rectangleEntity = dynamic_cast<RectangleEntity*>(target);
        if (rectangleEntity != nullptr)
        {
            return resolveCollision(rectangleEntity);
        }

        assert(false && "resolveCollision function of SphereEntity can't handle the target type entity\n");
        return false;
    }

    void SphereEntity::setRadius(float radius)
    {
        m_Radius = radius;
    }

    float SphereEntity::getRadius(void) const
    {
        return m_Radius;
    }

    float SphereEntity::getMaximumRadius(void) const
    {
        return m_Radius * std::max( std::max(m_Scale.mat[0][0], m_Scale.mat[1][1]), m_Scale.mat[2][2]);
    }

    float SphereEntity::distance(const SphereEntity* target)
    {
        return Dir3D(target->getPosition(), m_Position).magnitude();
    }

    bool SphereEntity::resolveCollision(SphereEntity* target)
    {
        (void) *target;
        /*result.fDistance = distance(target);
        result.distance = getPosition() - target->getPosition();
        result.fOverlap = 0.5f * (result.fDistance - getMaximumRadius() - target->getMaximumRadius());
        */
        std::cout << "SphereEntity::resolveCollision SphereEntity : " << target << std::endl;
        return false;
    }

    bool SphereEntity::resolveCollision(RectangleEntity* target)
    {
        Pos3D posSphere = getPosition() * target->getRotation().invert();
        float radiusSphere = getMaximumRadius();

        Pos3D posRectangle = target->getPosition();
        Vector3 sizeRectangle = target->getScaledSize();

        Pos3D vNearestPoint;
        vNearestPoint.x = std::max(posRectangle.x - sizeRectangle.x, std::min(posSphere.x, posRectangle.x + sizeRectangle.x));
        vNearestPoint.y = std::max(posRectangle.y - sizeRectangle.y, std::min(posSphere.y, posRectangle.y + sizeRectangle.y));
        vNearestPoint.z = std::max(posRectangle.z - sizeRectangle.z, std::min(posSphere.z, posRectangle.z + sizeRectangle.z));

        Dir3D vRayToNearest(posSphere, vNearestPoint);
        float fOverlap = radiusSphere - vRayToNearest.magnitude();
		if (std::isnan(fOverlap)) fOverlap = 0;

        //std::cout << "fOverlap : " << fOverlap << std::endl;
        if (fOverlap > 0)
		{
            posSphere = posSphere - vRayToNearest.normalize() * fOverlap;
            setPosition(posSphere * target->getRotation());
            return true;
        }

        return false;
    }
}