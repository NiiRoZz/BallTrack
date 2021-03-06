#ifndef _BALLTRACK_TG3D_H
#define _BALLTRACK_TG3D_H

#include <type_traits>

namespace BallTrack
{
	class TG3D
	{
	public:
		TG3D(void);
		TG3D(float value);

		template<typename T>
		T operator*(const T& rhs) const // Compose this et rhs (this.rhs) et retourne le resultat 
		{
			static_assert(std::is_base_of<TG3D, T>::value, "The template operator* should use a child class per default, specialize it, if you need to use it with another class");

			T res;

			for (int l = 0; l < 4; ++l)
			{
				for (int c = 0; c < 4; ++c)
				{
					res.mat[l][c] = 0.0f;

					for (int k = 0; k < 4; ++k)
					{ // [l][k] *[k][c] 
						res.mat[l][c] += this->mat[l][k] * rhs.mat[k][c];
					}
				}
			}

			return res;
		}

		TG3D transpose(void) const;
		TG3D invert(void) const;

	public:
		float mat[4][4];
	};
}

#endif //_BALLTRACK_TG3D_H