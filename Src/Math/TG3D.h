#ifndef _BALLTRACK_TG3D_H
#define _BALLTRACK_TG3D_H

namespace BallTrack
{
	class TG3D
	{
	public:
		TG3D(void);

		TG3D operator*(const TG3D& rhs) const;    // Compose this et rhs (this.rhs) et retourne le resultat 

	public:
		float mat[4][4];
	};
}

#endif //_BALLTRACK_TG3D_H