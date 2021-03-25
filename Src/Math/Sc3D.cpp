#include "Sc3D.h"

namespace BallTrack
{
	Sc3D::Sc3D(void)
	: Sc3D(1.0f)
	{
	}

	Sc3D::Sc3D(float s)
	: Sc3D(s, s, s)
	{
	}

	Sc3D::Sc3D(float sx, float sy, float sz)
	: TG3D()
	{
		mat[0][0] = sx;
		mat[1][1] = sy;
		mat[2][2] = sz;
	}
}
