#ifndef _DRAWABLE_H
#define _DRAWABLE_H

namespace BallTrack
{
    class Dir3D;

    class Drawable
    {
    public:
        virtual void render() = 0;
    };
}

#endif //_DRAWABLE_H