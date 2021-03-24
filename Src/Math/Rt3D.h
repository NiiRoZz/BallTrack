#ifndef _BALLTRACK_RT3D_H
#define _BALLTRACK_RT3D_H

#include "TG3D.h"

namespace BallTrack
{
	class Dir3D;

	class Rt3D : public TG3D
	{
	public:
		Rt3D(void);
		Rt3D(float angle, const Dir3D& dir);
	};
}

#endif //_BALLTRACK_RT3D_H