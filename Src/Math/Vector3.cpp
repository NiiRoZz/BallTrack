#include "Vector3.h"
#include "Pos3D.h"

namespace BallTrack
{
    Vector3::Vector3(void)
    : x(0.f), y(0.f), z(0.f)
    {
    }

    Vector3::Vector3(float xin, float yin, float zin)
    : x(xin), y(yin), z(zin)
    {
    }

    Vector3::Vector3(const Pos3D& pos)
    : Vector3(pos.x, pos.y, pos.z)
    {
    }
}