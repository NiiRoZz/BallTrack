#ifndef _BALLTRACK_CAMERA_H
#define _BALLTRACK_CAMERA_H
#include "Math/Pos3D.h"
#include "Math/Dir3D.h"


namespace BallTrack
{
	class TG3D;

	class Camera
	{
	public:
		Camera(const Pos3D& pos, const Pos3D& center, const Dir3D& up);
		TG3D getViewMatrix() const;
		void setPosition(const Pos3D& pos);
		void setCenter(const Pos3D center);

	private: 
		TG3D lookAt() const;
	private:
		Pos3D m_Position;
		Dir3D m_Up;
		Pos3D m_Center;

	};


}

#endif //_BALLTRACK_CAMERA_H
