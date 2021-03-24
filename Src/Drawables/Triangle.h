#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "Drawable.h"

namespace BallTrack
{
    class Triangle: public Drawable
    {
    public:
        virtual void render() override;
    };
}

#endif //_TRIANGLE_H
