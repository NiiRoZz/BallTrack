#ifndef _BALLTRACK_SC3D_H
#define _BALLTRACK_SC3D_H

#include "TG3D.h"

namespace BallTrack
{
	class Sc3D : public TG3D
	{
	public:
		Sc3D(void);
		Sc3D(float s);
		Sc3D(float sx, float sy, float sz);
	};
}

#endif //_BALLTRACK_SC3D_H