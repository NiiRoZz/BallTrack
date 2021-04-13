#include "Model3D.h"

#include <iostream>

namespace BallTrack
{
    Model3D::Model3D(const std::vector<Triangle>& triangles)
    : m_Triangles(triangles)
    {
    }
    
    void Model3D::setTriangles(const std::vector<Triangle>& triangles)
    {
        m_Triangles = triangles;
    }

    const std::vector<Triangle>& Model3D::getTriangles() const
    {
        return m_Triangles;
    }

    void Model3D::setTextureID(GLuint textureID)
    {
        m_textureID = textureID;
    }

    GLuint Model3D::getTextureID() const
    {
        return m_textureID;
    }

    void Model3D::render(const TG3D& parentMat)
    {
        if (m_Triangles.size() <= 0) return;

        for (Triangle& triangle: m_Triangles)
        {
            glBindTexture(GL_TEXTURE_2D, getTextureID());
            triangle.render(parentMat);
        }
    }
}