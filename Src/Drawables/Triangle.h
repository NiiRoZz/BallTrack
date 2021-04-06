#ifndef _BALLTRACK_TRIANGLE_H
#define _BALLTRACK_TRIANGLE_H

#if defined(WIN32) || defined(WIN64)
    #define NOMINMAX
#endif


#include <array>
#include <vector>

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
        Triangle(const std::vector<Vertex>& vertices);
        
        virtual void render(const TG3D& viewProjection, const TG3D& parentMat = TG3D()) override;

        const std::array<Vertex, 3>& getVertices();

    private:
        std::array<Vertex, 3> m_Vertices;
    };
}

#endif //_BALLTRACK_TRIANGLE_H
