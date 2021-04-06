#ifndef _BALLTRACK_DIR3D_H
#define _BALLTRACK_DIR3D_H

#include "CH3D.h"

namespace BallTrack
{
	class Pos3D;

	class Dir3D : public CH3D
	{
	public:
		Dir3D(void);
		Dir3D(float xp, float yp, float zp);
		Dir3D(const Pos3D &p1, const Pos3D &p2);  // Constructeur pour construire la direction p1 p2 
		Dir3D(const CH3D& ch);

		float magnitude(void) const;
		Dir3D normalize(void) const;
		Dir3D tangent(void) const;

		float operator*(const Dir3D& dir) const; // produit scalaire entre this et dir 
		Dir3D operator*(const float distance) const;
		Dir3D operator^(const Dir3D& dir) const; // produit vectoriel entre this et dir 
		Dir3D operator*(const TG3D& rhs) const;
	};
}

#endif //_BALLTRACK_DIR3D_H