#include "Triangle.h"

#include "Math/Sc3D.h"
#include "Math/Rt3D.h"
#include "Math/Tr3D.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

namespace BallTrack
{
    Triangle::Triangle(void)
    : Drawable()
    {
        m_Vertices[0] = Pos3D(0.f, 0.f, 0.f);
        m_Vertices[1] = Pos3D(1.f, 0.f, 0.f);
        m_Vertices[2] = Pos3D(0.f, 1.f, 0.f);
    }

    void Triangle::render()
    {
        glBegin(GL_TRIANGLES);
        for (Pos3D& pos: m_Vertices)
        {
            CH3D newPos = ((pos * m_Rotation) * m_Translation) * m_Scale;
            glVertex3f(newPos.x, newPos.y, newPos.z);
        }
        glEnd();
    }

    Triangle& Triangle::operator*(const Sc3D& scale)
    {
        for (Pos3D& pos: m_Vertices)
        {
            pos *= scale;
        }
        
        return *this;
    }

    Triangle& Triangle::operator*(const Rt3D& rotation)
    {
        for (Pos3D& pos: m_Vertices)
        {
            pos *= rotation;
        }

        return *this;
    }

    Triangle& Triangle::operator*(const Tr3D& translation)
    {
        for (Pos3D& pos: m_Vertices)
        {
            pos *= translation;
        }

        return *this;
    }

    const std::array<Pos3D, 3>& Triangle::getVertices()
    {
        return m_Vertices;
    }
}