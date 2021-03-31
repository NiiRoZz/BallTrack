#ifndef _BALLTRACK_VECTOR3_H
#define _BALLTRACK_VECTOR3_H

namespace BallTrack
{
    class Pos3D;
    
    class Vector3
    {
    public:
        Vector3(void);
        Vector3(float xin, float yin, float zin);
        Vector3(const Pos3D& pos);

    public:
        float x;
        float y;
        float z;
    };
}

#endif //_BALLTRACK_VECTOR3_H