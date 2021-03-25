#ifndef _BALLTRACK_MODEL3D_H
#define _BALLTRACK_MODEL3D_H

#include <filesystem>

#include "Drawable.h"
#include "Triangle.h"

namespace BallTrack
{
    class Model3D: public Drawable
    {
    public:
        Model3D(void) = default;
        Model3D(const std::vector<Triangle>& triangles);

        void setTriangles(const std::vector<Triangle>& triangles);

        virtual void render(const TG3D& parentMat = TG3D()) override;

    private:
        std::vector<Triangle> m_Triangles;
    };
}

#endif //_BALLTRACK_MODEL3D_H
