#include "Dir3D.h"

#include <math.h>

#include "Pos3D.h"

namespace BallTrack
{
	Dir3D::Dir3D(void)
	: CH3D(0.0f, 0.0f, 1.0f, 0.0f)
	{
	}

	Dir3D::Dir3D(float xp, float yp, float zp)
	: CH3D(xp, yp, zp, 0.0f)
	{
	}

	Dir3D::Dir3D(const Pos3D &p1, const Pos3D &p2)
	: CH3D(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z, 0.0f)
	{
	}

	float Dir3D::norme(void) const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	Dir3D Dir3D::normalize(void) const
	{
		float norm = norme();

		Dir3D res;

		if (norm != 0.0f)
		{
			res.x = x / norm;
			res.y = y / norm;
			res.z = z / norm;
		}

		return res;
	}

	float Dir3D::operator*(const Dir3D& dir)
	{
		return this->x * dir.x + this->y * dir.y + this->z * dir.z;
	}

	Dir3D Dir3D::operator^(const Dir3D& dir) // produit vectoriel entre this et dir 
	{
		Dir3D res;

		res.x = this->y * dir.z - dir.y * this->z;
		res.y = this->z * dir.x - dir.z * this->x;
		res.z = this->x * dir.y - dir.x * this->y;

		return res;
	}
}
