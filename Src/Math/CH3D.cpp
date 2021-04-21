#include "CH3D.h"
#include "TG3D.h"

namespace BallTrack
{
	CH3D::CH3D(void)
	: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{
	}

	CH3D::CH3D(float xp, float yp, float zp, float wp)
	: x(xp), y(yp), z(zp), w(wp)
	{
	}

	CH3D CH3D::operator*(const TG3D& mat) const
	{
		CH3D res;

		res.x = this->x * mat.mat[0][0] + this->y * mat.mat[0][1] + this->z * mat.mat[0][2] + this->w * mat.mat[0][3];
		res.y = this->x * mat.mat[1][0] + this->y * mat.mat[1][1] + this->z * mat.mat[1][2] + this->w * mat.mat[1][3];
		res.z = this->x * mat.mat[2][0] + this->y * mat.mat[2][1] + this->z * mat.mat[2][2] + this->w * mat.mat[2][3];
		res.w = this->x * mat.mat[3][0] + this->y * mat.mat[3][1] + this->z * mat.mat[3][2] + this->w * mat.mat[3][3];

		return res;
	}

	CH3D CH3D::operator*(const float size) const
	{
		return CH3D(x * size, y * size, z * size, w);
	}

	CH3D CH3D::operator/(const float size) const
	{
		return CH3D(x / size, y / size, z / size, w);
	}

	CH3D& CH3D::operator*=(const TG3D& rhs)
	{
		CH3D temp = *this;

		x = temp.x * rhs.mat[0][0] + temp.y * rhs.mat[0][1] + temp.z * rhs.mat[0][2] + temp.w * rhs.mat[0][3];
		y = temp.x * rhs.mat[1][0] + temp.y * rhs.mat[1][1] + temp.z * rhs.mat[1][2] + temp.w * rhs.mat[1][3];
		z = temp.x * rhs.mat[2][0] + temp.y * rhs.mat[2][1] + temp.z * rhs.mat[2][2] + temp.w * rhs.mat[2][3];
		w = temp.x * rhs.mat[3][0] + temp.y * rhs.mat[3][1] + temp.z * rhs.mat[3][2] + temp.w * rhs.mat[3][3];

		return *this;
	}

	CH3D& CH3D::operator*=(const float size)
	{
		x *= size;
		y *= size;
		z *= size;

		return *this;
	}

	CH3D& CH3D::operator+=(const CH3D& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}

	CH3D& CH3D::operator-=(const CH3D& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;

		return *this;
	}
}
