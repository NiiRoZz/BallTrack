#ifndef _BALLTRACK_MODEL3D_H
#define _BALLTRACK_MODEL3D_H

#include <vector>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

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
        const std::vector<Triangle>& getTriangles() const;

        void setTextureID(GLuint textureID);
        GLuint getTextureID() const;

        virtual void render(const TG3D& parentMat = TG3D()) override;

    protected:
        std::vector<Triangle> m_Triangles;
        GLuint m_textureID;
    };
}

#endif //_BALLTRACK_MODEL3D_H
