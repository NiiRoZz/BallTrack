#include "Rt3D.h"

#include <math.h>

#include "Dir3D.h"

namespace BallTrack
{
	Rt3D::Rt3D(void)
	: Rt3D(0.f, Dir3D(0.f, 0.f, 0.f))
	{
	}

	Rt3D::Rt3D(float angle, const Dir3D& dir)
	: TG3D()
	{
		float c = cosf(angle);
		float s = sinf(angle);

		Dir3D dirNorm = dir.normalize();

		mat[0][0] = dirNorm.x * dirNorm.x + c * (1.0f - dirNorm.x * dirNorm.x);
		mat[0][1] = dirNorm.x * dirNorm.y * (1.0f - c) - dirNorm.z * s;
		mat[0][2] = dirNorm.x * dirNorm.z * (1.0f - c) + dirNorm.y * s;

		mat[1][0] = dirNorm.x * dirNorm.y * (1.0f - c) + dirNorm.z * s;
		mat[1][1] = dirNorm.y * dirNorm.y + c * (1 - dirNorm.y * dirNorm.y);
		mat[1][2] = dirNorm.y * dirNorm.z * (1.0f - c) - dirNorm.x * s;

		mat[2][0] = dirNorm.x * dirNorm.z * (1.0f - c) - dirNorm.y * s;
		mat[2][1] = dirNorm.y * dirNorm.z * (1.0f - c) + dirNorm.x * s;
		mat[2][2] = dirNorm.z * dirNorm.z + c * (1 - dirNorm.z * dirNorm.z);
	}
}
