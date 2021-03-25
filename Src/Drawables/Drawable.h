#ifndef _BALLTRACK_DRAWABLE_H
#define _BALLTRACK_DRAWABLE_H

#include "Math/Sc3D.h"
#include "Math/Rt3D.h"
#include "Math/Tr3D.h"

namespace BallTrack
{
    class Drawable
    {
    public:
        virtual void render(const TG3D& parentMat = TG3D()) = 0;

        const Sc3D& getScale();
        void setScale(const Sc3D& scale);

        const Rt3D& getRotation();
        void setRotation(const Rt3D& rotation);

        const Tr3D& getTranslation();
        void setTranslation(const Tr3D& translation);

        TG3D getModelMatrix(void) const;

    protected:
        Sc3D m_Scale;
        Rt3D m_Rotation;
        Tr3D m_Translation;
    };
}

#endif //_BALLTRACK_DRAWABLE_H