#ifndef _BALLTRACK_POS3D_H
#define _BALLTRACK_POS3D_H

#include "CH3D.h"

namespace BallTrack
{
	class Pos3D : public CH3D
	{
	public:
		Pos3D(void);
		Pos3D(float xp, float yp, float zp);
	};
}

#endif //_BALLTRACK_POS3D_H
