#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include <array>

#include "Drawable.h"

#include "Math/Pos3D.h"

namespace BallTrack
{
    class Sc3D;
    class Rt3D;
    class Tr3D;

    class Triangle: public Drawable
    {
    public:
        Triangle(void);
        
        virtual void render() override;

        Triangle& operator*(const Sc3D& scale);
        Triangle& operator*(const Rt3D& rotation);
        Triangle& operator*(const Tr3D& translation);

        const std::array<Pos3D, 3>& getVertices();

    private:
        std::array<Pos3D, 3> m_Vertices;
    };
}

#endif //_TRIANGLE_H
