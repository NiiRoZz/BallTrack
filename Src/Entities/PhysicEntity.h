#ifndef _BALLTRACK_PHYSICENTITY_H
#define _BALLTRACK_PHYSICENTITY_H

#include <memory>

#include "Entities/Entity.h"
#include "Physics/CollisionPrimitive.h"

#include "Math/Vector3.h"
#include "Math/Pos3D.h"
#include "Math/Dir3D.h"

namespace BallTrack
{
    class PhysicEntity: public Entity
    {
    public:
        PhysicEntity(void);
        PhysicEntity(const Model3D& model, bool _static);

        virtual void render(const TG3D& parentMat = TG3D()) override;

        void addCollisionPrimitive(std::unique_ptr<CollisionPrimitive>&& primitive);

        void update(float dtSeconds);

        bool resolveCollision(PhysicEntity* target);
        void dynamicCollision(PhysicEntity* target);

        const Dir3D& getAcceleration() const;

        const Dir3D& getVelocity() const;
        void setVelocity(const Dir3D& velocity);

        float getMass() const;
        void setMass(float mass);

        bool isStatic() const;
        void setStatic(bool _static);

    protected:
        Dir3D m_Acceleration;
        Dir3D m_Velocity;
        float m_Mass;

        bool m_Static;

        std::vector<std::unique_ptr<CollisionPrimitive>> m_CollisionPrimitives;
    };
}

#endif //_BALLTRACK_PHYSICENTITY_H