#ifndef _BALLTRACK_TRIANGLE_H
#define _BALLTRACK_TRIANGLE_H

#include <array>

#include "Drawable.h"
#include "Vertex.h"

namespace BallTrack
{
    class Sc3D;
    class Rt3D;
    class Tr3D;

    class Triangle: public Drawable
    {
    public:
        Triangle(void);
        
        virtual void render(const TG3D& parentMat = TG3D()) override;

        const std::array<Vertex, 3>& getVertices();

    private:
        std::array<Vertex, 3> m_Vertices;
    };
}

#endif //_BALLTRACK_TRIANGLE_H
