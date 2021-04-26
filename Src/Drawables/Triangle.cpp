#include "Triangle.h"

#include "Math/Sc3D.h"
#include "Math/Rt3D.h"
#include "Math/Tr3D.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

#define NOMINMAX

namespace BallTrack
{
    Triangle::Triangle(void)
    : Drawable()
    {

    }

    Triangle::Triangle(const std::vector<Vertex>& vertices)
    : Drawable()
    {
        std::size_t min = std::min(m_Vertices.size(), vertices.size());

        for (std::size_t i = 0; i < min; ++i)
        {
            m_Vertices[i] = vertices[i];
        }
    }

    void Triangle::render(const TG3D& parentMat)
    {
        const TG3D normalMatrix = parentMat.transpose().invert();

        glBegin(GL_TRIANGLES);
        for (const Vertex& vertex: m_Vertices)
        {
            CH3D newPos = vertex.position * parentMat;
            Dir3D newNormal = vertex.normal * normalMatrix;
            newNormal = newNormal.normalize();

            //std::cout << "normal.x : " << vertex.normal.x << " normal.y : " << vertex.normal.y << " normal.z : " << vertex.normal.z << std::endl;
            //std::cout << "uv.x : " << vertex.uv.x << " uv.y : " << vertex.uv.y << std::endl;

            glTexCoord2f(vertex.uv.x, vertex.uv.y);
            glNormal3f(newNormal.x, newNormal.y, newNormal.z);
            glVertex3f(newPos.x, newPos.y, newPos.z);
        }
        glEnd();

        /* Show normals ?
        glBegin(GL_LINES);
        for (const Vertex& vertex: m_Vertices)
        {
            CH3D newPos = vertex.position * MVP;
            Dir3D newNormal = vertex.normal * normalMatrix;
            newNormal = newNormal.normalize();

            Pos3D nextPoint = Pos3D(newNormal * 0.5f) + newPos;

            //std::cout << "nextPoint.x : " << nextPoint.x << " nextPoint.y : " << nextPoint.y << " nextPoint.z : " << nextPoint.z << std::endl;

            //glColor3f(1.f, 0.f, 0.f);
            glVertex3f(newPos.x, newPos.y, newPos.z);
            glVertex3f(nextPoint.x, nextPoint.y, nextPoint.z);
        }
        glEnd();
        */
    }

    const std::array<Vertex, 3>& Triangle::getVertices()
    {
        return m_Vertices;
    }
}