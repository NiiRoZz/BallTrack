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
        Model3D(void);
        Model3D(std::vector<Triangle>& triangles);

        bool isValid(void) const;

        virtual void render(const TG3D& parentMat = TG3D()) override;

    private:
        bool m_Valid;
        std::vector<Triangle> m_Triangles;
    };
}

#endif //_BALLTRACK_MODEL3D_H
