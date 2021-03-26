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
    };
}

#endif //_BALLTRACK_DRAWABLE_H