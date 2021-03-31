#ifndef _BALLTRACK_RECTANGLEENTITY_H
#define _BALLTRACK_RECTANGLEENTITY_H

#include "Physics/PhysicEntity.h"

namespace BallTrack
{
    class RectangleEntity: public PhysicEntity
    {
    public:
        RectangleEntity(void);
        RectangleEntity(const Model3D& model);

        virtual bool resolveCollision(PhysicEntity* target) override;

        virtual void update(float dtSeconds) override;

        const Vector3& getSize(void) const;
        Vector3 getScaledSize(void) const;
        void setSize(Vector3 size);

    private:
        Vector3 m_Size;
    };
}

#endif //_BALLTRACK_RECTANGLEENTITY_H