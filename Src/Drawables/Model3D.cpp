#include "Model3D.h"

#include <iostream>

namespace BallTrack
{
    Model3D::Model3D(void)
    : m_Valid(false)
    {
    }

    Model3D::Model3D(std::vector<Triangle>& triangles)
    : m_Valid(true)
    , m_Triangles(triangles)
    {
    }

    bool Model3D::isValid(void) const
    {
        return m_Valid;
    }

    void Model3D::render(const TG3D& parentMat)
    {
        if (!isValid()) return;

        TG3D modelMatrix = parentMat * getModelMatrix();

        for (Triangle& triangle: m_Triangles)
        {
            triangle.render(modelMatrix);
        }
    }
}