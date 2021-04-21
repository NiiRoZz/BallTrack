#ifndef _BALLTRACK_POS3D_H
#define _BALLTRACK_POS3D_H

#include "CH3D.h"

namespace BallTrack
{
	class Dir3D;
	class Vector3;

	class Pos3D : public CH3D
	{
	public:
		Pos3D(void);
		Pos3D(float xp, float yp, float zp);
		Pos3D(const Vector3& vec);
		Pos3D(float distance, const Dir3D& dir);
		Pos3D(const CH3D& ch);

		Pos3D operator+(const Pos3D& rhs) const;
		Pos3D operator+(const CH3D& rhs) const;

		Pos3D operator-(const Pos3D& rhs) const;

		CH3D operator*(const Pos3D& rhs) const;
		CH3D operator*(const TG3D& rhs) const;
	};
}

#endif //_BALLTRACK_POS3D_H
