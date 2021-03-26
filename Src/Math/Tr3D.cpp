#include "Tr3D.h"
#include "Dir3D.h"
#include "Pos3D.h"

namespace BallTrack
{
	Tr3D::Tr3D(void)
	: Tr3D(0.f, 0.f, 0.f)
	{

	}

	Tr3D::Tr3D(float tx, float ty, float tz)
	: TG3D()
	{
		mat[0][3] = tx;
		mat[1][3] = ty;
		mat[2][3] = tz;
	}

	Tr3D::Tr3D(const Dir3D& dir)
	: Tr3D(dir.x, dir.y, dir.z)
	{
	}

	Tr3D::Tr3D(const Pos3D& pos)
	: Tr3D(pos.x, pos.y, pos.z)
	{
	}
}
