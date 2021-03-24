#ifndef _DRAWABLE_H
#define _DRAWABLE_H

#include "Math/Pos3D.h"

namespace BallTrack
{
    class Drawable
    {
    public:
        virtual void render() = 0;

    private:
        Pos3D m_Pos;
    };
}

#endif //_DRAWABLE_H