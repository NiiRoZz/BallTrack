#ifndef _BALLTRACK_TR3D_H
#define _BALLTRACK_TR3D_H

#include "TG3D.h"

namespace BallTrack
{
	class Dir3D;

	class Tr3D : public TG3D
	{
	public:
		Tr3D(float tx, float ty, float tz);
		Tr3D(const Dir3D& dir);
	};
}

#endif //_BALLTRACK_TR3D_H