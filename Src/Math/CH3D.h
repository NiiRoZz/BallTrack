#ifndef _BALLTRACK_CH3D_H
#define _BALLTRACK_CH3D_H

#include <iostream>

namespace BallTrack
{
	class TG3D;

	class CH3D
	{
	public:
		CH3D(void);
		CH3D(float xp, float yp, float zp, float wp);

		CH3D operator*(const TG3D& rhs) const;
		CH3D operator*(const float size) const;
		CH3D operator/(const float size) const;
		CH3D& operator*=(const TG3D& rhs);
		CH3D& operator*=(const float size);
		CH3D& operator+=(const CH3D& rhs);
		CH3D& operator-=(const CH3D& rhs);

	public:
		float x, y, z;

	private:
		float w;
	};
}

#endif //_BALLTRACK_CH3D_H