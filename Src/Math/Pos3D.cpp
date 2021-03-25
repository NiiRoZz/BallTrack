#include "Pos3D.h"

namespace BallTrack
{
    Pos3D::Pos3D(void)
    : CH3D()
    {
    }

    Pos3D::Pos3D(float xp, float yp, float zp)
    : CH3D(xp, yp, zp, 1.0f)
    {
    }
}
