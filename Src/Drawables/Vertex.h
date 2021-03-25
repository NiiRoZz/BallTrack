#ifndef _BALLTRACK_VERTEX_H
#define _BALLTRACK_VERTEX_H

#include "Math/Pos3D.h"
#include "Math/Dir3D.h"
#include "Math/Vector2.h"

namespace BallTrack
{
	struct Vertex
    {
        Pos3D position;
        Dir3D normal;
        Vector2 uv;
    };
}

#endif //_BALLTRACK_VERTEX_H