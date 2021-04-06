#include "Camera.h"
#include "Math/TG3D.h"

namespace BallTrack
{
	Camera::Camera(const Pos3D& pos, const Pos3D& center, const Dir3D& up)
	: m_Position(pos)
	, m_Up(up)
	, m_Center(center)
	{
		
	}
	TG3D Camera::getViewMatrix() const
	{
		return lookAt();
	}

	void Camera::setPosition(const Pos3D& pos)
	{
		m_Position = pos;
	}

	void Camera::setCenter(const Pos3D center)
	{
		m_Center = center;
	}

	TG3D Camera::lookAt() const
	{
		TG3D result;

		const Dir3D f = Dir3D(m_Position, m_Center).normalize();
		const Dir3D s = (f ^ m_Up).normalize();
		const Dir3D u = s ^ f;

		result.mat[0][0] = s.x;
		result.mat[0][1] = s.y;
		result.mat[0][2] = s.z;
		result.mat[1][0] = u.x;
		result.mat[1][1] = u.y;
		result.mat[1][2] = u.z;
		result.mat[2][0] = -f.x;
		result.mat[2][1] = -f.y;
		result.mat[2][2] = -f.z;
		result.mat[0][3] = -(s * m_Position);
		result.mat[1][3] = -(u * m_Position);
		result.mat[2][3] = (f * m_Position);
		return result;
	}

}
