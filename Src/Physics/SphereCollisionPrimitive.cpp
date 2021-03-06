#include "Physics/SphereCollisionPrimitive.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <cassert>
#include <cmath>

#include "Physics/RectangleCollisionPrimitive.h"
#include "Entities/PhysicEntity.h"

namespace BallTrack
{
    SphereCollisionPrimitive::SphereCollisionPrimitive(PhysicEntity* parent)
    : CollisionPrimitive(parent)
    {
    }

    void SphereCollisionPrimitive::render(const TG3D& parentMat)
    {
        const TG3D modelMat = parentMat * getModelMatrix();

        float r = getMaximumRadius();
        int nParal = 20;
        int nMerid = 20;

        Pos3D pos;

        for (float j = 0; j < M_PI; j += M_PI/(nParal+1))
        {
            glBegin(GL_LINE_LOOP);
            pos.y = (float) (r * cosf(j));
            for(float i = 0; i<2*M_PI; i+=M_PI/60)
            {
                pos.x = (float) (r*std::cos(i)*std::sin(j));
                pos.z = (float) (r*std::sin(i)*std::sin(j));

                CH3D newPos = pos * modelMat;
                glVertex3f(newPos.x, newPos.y, newPos.z);
            }
            glEnd();
        }

        for(float j = 0; j < M_PI; j += M_PI/nMerid)
        {
            glBegin(GL_LINE_LOOP);
            for(float i = 0; i < 2*M_PI; i += M_PI/60)
            {
                pos.x = (float) (r*std::sin(i)*std::cos(j));
                pos.y = (float) (r*std::cos(i));
                pos.z = (float) (r*std::sin(j)*std::sin(i));
                
                CH3D newPos = pos * modelMat;
                glVertex3f(newPos.x, newPos.y, newPos.z);
            }
            glEnd();
        }

        /*
        int lats = nParal;
        int longs = nMerid;

        for(int i = 0; i <= lats; ++i) {
            double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
            double z0  = sin(lat0);
            double zr0 =  cos(lat0);

            double lat1 = M_PI * (-0.5 + (double) i / lats);
            double z1 = sin(lat1);
            double zr1 = cos(lat1);

            glBegin(GL_QUAD_STRIP);
            for(int j = 0; j <= longs; ++j) {
                double lng = 2 * M_PI * (double) (j - 1) / longs;
                double x = cos(lng);
                double y = sin(lng);

                CH3D newPos = Pos3D(r * x * zr0, r * y * zr0, r * z0) * MVP;
                glVertex3f(newPos.x, newPos.y, newPos.z);

                newPos = Pos3D(r * x * zr1, r * y * zr1, r * z1) * MVP;
                glVertex3f(newPos.x, newPos.y, newPos.z);
            }
            glEnd();
        }
        */
    }

    bool SphereCollisionPrimitive::resolveCollision(CollisionPrimitive* target)
    {
        SphereCollisionPrimitive* sphereCollision = dynamic_cast<SphereCollisionPrimitive*>(target);
        if (sphereCollision != nullptr)
        {
            return resolveCollision(sphereCollision);
        }

        RectangleCollisionPrimitive* rectangleEntity = dynamic_cast<RectangleCollisionPrimitive*>(target);
        if (rectangleEntity != nullptr)
        {
            return resolveCollision(rectangleEntity);
        }

        assert(false && "resolveCollision function of SphereCollisionPrimitive can't handle the target collision primitive type\n");
        return false;
    }

    TG3D SphereCollisionPrimitive::getModelMatrix() const
    {
        return Tr3D(m_Position) * m_Rotation * Sc3D(getMaximumRadius());
    }

    void SphereCollisionPrimitive::setRadius(float radius)
    {
        m_Radius = radius;
    }

    float SphereCollisionPrimitive::getRadius(void) const
    {
        return m_Radius;
    }

    float SphereCollisionPrimitive::getMaximumRadius() const
    {
        const Sc3D& scale = getScale();
        return m_Radius * std::max( std::max(scale.mat[0][0], scale.mat[1][1]), scale.mat[2][2]);
    }

    float SphereCollisionPrimitive::distance(const SphereCollisionPrimitive* target)
    {
        return Dir3D(target->getPosition(), getPosition()).magnitude();
    }

    bool SphereCollisionPrimitive::resolveCollision(SphereCollisionPrimitive* target)
    {
        PhysicEntity* parent = getParent();
        if (parent == nullptr) return false;

        PhysicEntity* parentTarget = target->getParent();
        if (parentTarget == nullptr) return false;

        float sphereRadius = getMaximumRadius();
        float targetRadius = target->getMaximumRadius();

        Pos3D parentPosition = parent->getPosition();
        Pos3D parentTargetPosition = parentTarget->getPosition();

        Pos3D spherePosition = getPosition();
        Pos3D targetPosition = target->getPosition();

        float fDistance = distance(target);

        //Overlap
        if ((fDistance * fDistance) <= ((sphereRadius + targetRadius) * (sphereRadius + targetRadius)))
        {
            float fOverlap = 0.5f * (fDistance - sphereRadius - targetRadius);
            Pos3D diffPosition = spherePosition - targetPosition;

            parentPosition -= diffPosition * fOverlap / fDistance;
            parent->setPosition(parentPosition);

            diffPosition = getPosition() - targetPosition;
            parentTargetPosition += diffPosition * fOverlap / fDistance;
            parentTarget->setPosition(parentTargetPosition);

            return true;
        }

        return false;
    }

    bool SphereCollisionPrimitive::resolveCollision(RectangleCollisionPrimitive* target)
    {
        PhysicEntity* parent = getParent();
        if (parent == nullptr) return false;

        Pos3D diff = getOffsetFromParent();

        const TG3D& targetRotation = target->getRotation();
        TG3D targetInverseRotation = targetRotation.invert();

        Pos3D posSphere = getPosition() * targetInverseRotation;
        float radiusSphere = getMaximumRadius();

        Pos3D posRectangle = target->getPosition() * targetInverseRotation;
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
            Pos3D newPosSphere = posSphere * targetRotation;
            parent->setPosition(newPosSphere - diff);

            //Dir3D parentVelocity = parent->getVelocity();
            //parentVelocity -= fOverlap * (parentVelocity * vRayToNearest);

            //parent->setVelocity(parentVelocity);

            return true;
        }

        return false;
    }
}