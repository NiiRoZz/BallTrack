#include "TG3D.h"

#include <iostream>

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

	TG3D::TG3D(float value)
	{
		for (int l = 0; l < 4; ++l)
		{
			for (int c = 0; c < 4; ++c)
			{
				mat[l][c] = value;
			}
		}
	}

	TG3D TG3D::transpose(void) const
	{
		TG3D result;

		for (int l = 0; l < 4; ++l)
		{
			for (int c = 0; c < 4; ++c)
			{
				result.mat[c][l] = mat[l][c];
			}
		}

		return result;
	}

	TG3D TG3D::invert(void) const
	{
		TG3D result;
		
		float s0 = mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];
		float s1 = mat[0][0] * mat[1][2] - mat[1][0] * mat[0][2];
		float s2 = mat[0][0] * mat[1][3] - mat[1][0] * mat[0][3];
		float s3 = mat[0][1] * mat[1][2] - mat[1][1] * mat[0][2];
		float s4 = mat[0][1] * mat[1][3] - mat[1][1] * mat[0][3];
		float s5 = mat[0][2] * mat[1][3] - mat[1][2] * mat[0][3];

		float c5 = mat[2][2] * mat[3][3] - mat[3][2] * mat[2][3];
		float c4 = mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3];
		float c3 = mat[2][1] * mat[3][2] - mat[3][1] * mat[2][2];
		float c2 = mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3];
		float c1 = mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2];
		float c0 = mat[2][0] * mat[3][1] - mat[3][0] * mat[2][1];

		float determinant = 1.0f / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

		result.mat[0][0] = ( mat[1][1] * c5 - mat[1][2] * c4 + mat[1][3] * c3) * determinant;
		result.mat[0][1] = (-mat[0][1] * c5 + mat[0][2] * c4 - mat[0][3] * c3) * determinant;
		result.mat[0][2] = ( mat[3][1] * s5 - mat[3][2] * s4 + mat[3][3] * s3) * determinant;
		result.mat[0][3] = (-mat[2][1] * s5 + mat[2][2] * s4 - mat[2][3] * s3) * determinant;

		result.mat[1][0] = (-mat[1][0] * c5 + mat[1][2] * c2 - mat[1][3] * c1) * determinant;
		result.mat[1][1] = ( mat[0][0] * c5 - mat[0][2] * c2 + mat[0][3] * c1) * determinant;
		result.mat[1][2] = (-mat[3][0] * s5 + mat[3][2] * s2 - mat[3][3] * s1) * determinant;
		result.mat[1][3] = ( mat[2][0] * s5 - mat[2][2] * s2 + mat[2][3] * s1) * determinant;

		result.mat[2][0] = ( mat[1][0] * c4 - mat[1][1] * c2 + mat[1][3] * c0) * determinant;
		result.mat[2][1] = (-mat[0][0] * c4 + mat[0][1] * c2 - mat[0][3] * c0) * determinant;
		result.mat[2][2] = ( mat[3][0] * s4 - mat[3][1] * s2 + mat[3][3] * s0) * determinant;
		result.mat[2][3] = (-mat[2][0] * s4 + mat[2][1] * s2 - mat[2][3] * s0) * determinant;

		result.mat[3][0] = (-mat[1][0] * c3 + mat[1][1] * c1 - mat[1][2] * c0) * determinant;
		result.mat[3][1] = ( mat[0][0] * c3 - mat[0][1] * c1 + mat[0][2] * c0) * determinant;
		result.mat[3][2] = (-mat[3][0] * s3 + mat[3][1] * s1 - mat[3][2] * s0) * determinant;
		result.mat[3][3] = ( mat[2][0] * s3 - mat[2][1] * s1 + mat[2][2] * s0) * determinant;

		return result;
	}
}
