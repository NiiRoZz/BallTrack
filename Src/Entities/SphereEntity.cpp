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

    void SphereEntity::dynamicCollision(PhysicEntity* target)
    {
        SphereEntity* sphereEntity = dynamic_cast<SphereEntity*>(target);
        if (sphereEntity != nullptr)
        {
            dynamicCollision(sphereEntity);
            return;
        }

        RectangleEntity* rectangleEntity = dynamic_cast<RectangleEntity*>(target);
        if (rectangleEntity != nullptr)
        {
            dynamicCollision(rectangleEntity);
            return;
        }

        assert(false && "dynamicCollision function of SphereEntity can't handle the target type entity\n");
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
        float sphereRadius = getMaximumRadius();
        float targetRadius = target->getMaximumRadius();

        Pos3D spherePosition = getPosition();
        Pos3D targetPosition = target->getPosition();
        Pos3D diffPosition = spherePosition - targetPosition;

        float fDistance = distance(target);

        //Overlap
        if (fDistance <= (sphereRadius + targetRadius))
        {
            float fOverlap = 0.5f * (fDistance - sphereRadius - targetRadius);

            spherePosition += diffPosition * fOverlap / fDistance;
            setPosition(spherePosition);

            diffPosition = spherePosition - targetPosition;
            targetPosition += diffPosition * fOverlap / fDistance;
            target->setPosition(targetPosition);

            return true;
        }

        return false;
    }

    bool SphereEntity::resolveCollision(RectangleEntity* target)
    {
        TG3D inverseRot = target->getRotation().invert();

        Pos3D posSphere = getPosition() * inverseRot;
        float radiusSphere = getMaximumRadius();

        Pos3D posRectangle = target->getPosition() * inverseRot;
        Vector3 sizeRectangle = target->getScaledSize();

        Pos3D vNearestPoint;
        vNearestPoint.x = std::max(posRectangle.x - sizeRectangle.x, std::min(posSphere.x, posRectangle.x + sizeRectangle.x));
        vNearestPoint.y = std::max(posRectangle.y - sizeRectangle.y, std::min(posSphere.y, posRectangle.y + sizeRectangle.y));
        vNearestPoint.z = std::max(posRectangle.z - sizeRectangle.z, std::min(posSphere.z, posRectangle.z + sizeRectangle.z));

        Dir3D vRayToNearest(posSphere, vNearestPoint);
        float fOverlap = radiusSphere - vRayToNearest.magnitude();
		if (std::isnan(fOverlap)) fOverlap = 0;
        
        if (fOverlap > 0)
		{
            posSphere = posSphere - vRayToNearest.normalize() * fOverlap;
            setPosition(posSphere * target->getRotation());

            return true;
        }

        return false;
    }

    void SphereEntity::dynamicCollision(SphereEntity* target)
    {
        Pos3D spherePosition = getPosition();
        Pos3D targetPosition = target->getPosition();

        Dir3D sphereVelocity = getVelocity();
        Dir3D targetVelocity = getVelocity();

        float sphereMass = getMass();
        float targetMass = target->getMass();

        float fDistance = distance(target);

        Dir3D normal = Dir3D(spherePosition, targetPosition) / fDistance;

        // Tangent
        float tx = -normal.y;
        float ty = normal.x;
        float tz = normal.z;

        float dpTan1 = sphereVelocity.x * tx + sphereVelocity.y * ty + sphereVelocity.z * tz;
		float dpTan2 = targetVelocity.x * tx + targetVelocity.y * ty + targetVelocity.z * tz;

        float dpNorm1 = sphereVelocity.x * normal.x + sphereVelocity.y * normal.y + sphereVelocity.z * normal.z;
		float dpNorm2 = targetVelocity.x * normal.x + targetVelocity.y * normal.y + targetVelocity.z * normal.z;

        float m1 = (dpNorm1 * (sphereMass - targetMass) + 2.0f * targetMass * dpNorm2) / (sphereMass + targetMass);
		float m2 = (dpNorm2 * (targetMass - sphereMass) + 2.0f * sphereMass * dpNorm1) / (sphereMass + targetMass);

        sphereVelocity.x = tx * dpTan1 + normal.x * m1;
        sphereVelocity.y = ty * dpTan1 + normal.y * m1;
        sphereVelocity.z = tz * dpTan1 + normal.z * m1;
        setVelocity(sphereVelocity);

        targetVelocity.x = tx * dpTan2 + normal.x * m2;
        targetVelocity.y = ty * dpTan2 + normal.y * m2;
        targetVelocity.z = tz * dpTan2 + normal.z * m2;
        target->setVelocity(targetVelocity);

        std::cout << "dynamicCollision SphereEntity" << std::endl;
    }

    void SphereEntity::dynamicCollision(RectangleEntity* target)
    {
        (void) target;
        std::cout << "dynamicCollision RectangleEntity" << std::endl;
    }
}