#include "TG3D.h"

namespace BallTrack
{
	TG3D::TG3D(void)
	{
		for (int l = 0; l < 4; ++l)
		{
			for (int c = 0; c < 4; ++c)
			{
				mat[l][c] = (l == c) ? 1.0f : 0.0f;
			}
		}
	}
}
