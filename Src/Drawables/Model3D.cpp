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

    void Model3D::render(const TG3D& parentMat)
    {
        if (m_Triangles.size() <= 0) return;

        TG3D modelMatrix = parentMat * getModelMatrix();

        for (Triangle& triangle: m_Triangles)
        {
            triangle.render(modelMatrix);
        }
    }
}