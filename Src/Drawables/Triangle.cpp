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
        m_Vertices[0] = Vertex {Pos3D(0.f, 0.f, 0.f), Dir3D(), Vector2()};
        m_Vertices[1] = Vertex {Pos3D(1.f, 0.f, 0.f), Dir3D(), Vector2()};
        m_Vertices[2] = Vertex {Pos3D(0.f, 1.f, 0.f), Dir3D(), Vector2()};
    }

    void Triangle::render()
    {
        glBegin(GL_TRIANGLES);
        for (Vertex& vertex: m_Vertices)
        {
            CH3D newPos = ((vertex.position * m_Rotation) * m_Translation) * m_Scale;

            glTexCoord2f(vertex.uv.x, vertex.uv.y);
            glNormal3f(vertex.normal.x, vertex.normal.y, vertex.normal.z);
            glVertex3f(newPos.x, newPos.y, newPos.z);
        }
        glEnd();
    }

    const std::array<Vertex, 3>& Triangle::getVertices()
    {
        return m_Vertices;
    }
}