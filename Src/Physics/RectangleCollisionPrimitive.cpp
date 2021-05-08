#include "Physics/RectangleCollisionPrimitive.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <cassert>

#include "Physics/SphereCollisionPrimitive.h"

namespace BallTrack
{
    RectangleCollisionPrimitive::RectangleCollisionPrimitive(PhysicEntity* parent)
    : CollisionPrimitive(parent)
    {
    }

    void RectangleCollisionPrimitive::render(const TG3D& parentMat)
    {
        const TG3D modelMat = parentMat * getModelMatrix();

        //Pos3D sizeRectangle = getScaledSize();

        static Pos3D v[8] = {
            {-1.f, -1.f, 1.f},
            {-1.f, 1.f, 1.f},
            {-1.f, -1.f, -1.f},
            {-1.f, 1.f, -1.f},
            {1.f, -1.f, 1.f},
            {1.f, 1.f, 1.f},
            {1.f, -1.f, -1.f},
            {1.f, 1.f, -1.f},
        };

        static int f[12][3] = {
            {2, 3, 1},
            {4, 7, 3},
            {8, 5, 7},
            {6, 1, 5},
            {7, 1, 3},
            {4, 6, 8},
            {2, 4, 3},
            {4, 8, 7},
            {8, 6, 5},
            {6, 2, 1},
            {7, 5, 1},
            {4, 2, 6},
        };

        for (int i = 0; i < 12; ++i)
        {
            glBegin(GL_LINES);

            CH3D firstVertex = v[f[i][0] - 1] * modelMat;
            CH3D secondVertex = v[f[i][1] - 1] * modelMat;
            CH3D thirdVertex = v[f[i][2] - 1] * modelMat;
            
            glVertex3f(firstVertex.x, firstVertex.y, firstVertex.z);
            glVertex3f(secondVertex.x, secondVertex.y, secondVertex.z);

            glVertex3f(firstVertex.x, firstVertex.y, firstVertex.z);
            glVertex3f(thirdVertex.x, thirdVertex.y, thirdVertex.z);

            glVertex3f(secondVertex.x, secondVertex.y, secondVertex.z);
            glVertex3f(thirdVertex.x, thirdVertex.y, thirdVertex.z);

            glEnd();
        }
    }

    bool RectangleCollisionPrimitive::resolveCollision(CollisionPrimitive* target)
    {
        SphereCollisionPrimitive* sphereCollision = dynamic_cast<SphereCollisionPrimitive*>(target);
        if (sphereCollision != nullptr)
        {
            return sphereCollision->resolveCollision((CollisionPrimitive*) this);
        }

        RectangleCollisionPrimitive* rectangleCollision = dynamic_cast<RectangleCollisionPrimitive*>(target);
        if (rectangleCollision != nullptr)
        {
            return false;
        }
        
        assert(false && "resolveCollision function of RectangleCollisionPrimitive can't handle the target collision primitive type\n");
        return false;
    }

    TG3D RectangleCollisionPrimitive::getModelMatrix() const
    {
        return Tr3D(m_Position) * m_Rotation * Sc3D(m_Size.x, m_Size.y, m_Size.z);
    }

    const Vector3& RectangleCollisionPrimitive::getSize(void) const
    {
        return m_Size;
    }

    Vector3 RectangleCollisionPrimitive::getScaledSize(void) const
    {
        const Sc3D& scale = getScale();
        return Vector3(m_Size.x * scale.mat[0][0], m_Size.y * scale.mat[1][1], m_Size.z * scale.mat[2][2]);
    }

    void RectangleCollisionPrimitive::setSize(const Vector3& size)
    {
        m_Size = size;
    }
}