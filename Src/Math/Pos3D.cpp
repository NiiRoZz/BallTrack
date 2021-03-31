#include "Pos3D.h"

#include "Dir3D.h"

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

    Pos3D::Pos3D(float distance, const Dir3D& dir)
    : CH3D()
    {
        const Pos3D& pos = dir.normalize() * distance;
        x = pos.x;
        y = pos.y;
        z = pos.z;
    }

    Pos3D::Pos3D(const CH3D& ch)
    : CH3D(ch.x, ch.y, ch.z, 1.0f)
    {
    }

    Pos3D Pos3D::operator+(const Pos3D& rhs) const
    {
        return Pos3D(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    Pos3D Pos3D::operator+(const CH3D& rhs) const
    {
        return Pos3D(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    Pos3D Pos3D::operator-(const Pos3D& rhs) const
    {
        return Pos3D(x - rhs.x, y - rhs.y, z - rhs.z);
    }
}
