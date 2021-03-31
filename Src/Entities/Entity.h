#ifndef _BALLTRACK_ENTITY_H
#define _BALLTRACK_ENTITY_H

#include "Drawables/Drawable.h"
#include "Drawables/Model3D.h"
#include "Math/Pos3D.h"
#include "Math/Sc3D.h"
#include "Math/Rt3D.h"

namespace BallTrack
{
    class Entity: public Drawable
    {
    public:
        Entity(void) = default;
        Entity(const Model3D& model);

        virtual void render(const TG3D& parentMat = TG3D()) override;

        const Sc3D& getScale() const;
        void setScale(const Sc3D& scale);

        const Rt3D& getRotation() const;
        void setRotation(const Rt3D& rotation);

        const Pos3D& getPosition(void) const;
        void setPosition(const Pos3D& pos);

        TG3D getModelMatrix(void) const;

    protected:
        Pos3D m_Position;
        Sc3D m_Scale;
        Rt3D m_Rotation;
        Model3D m_Model3D;
    };
}

#endif //_BALLTRACK_ENTITY_H