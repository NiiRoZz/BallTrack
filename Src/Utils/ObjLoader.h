#ifndef _BALLTRACK_OBJLOADER_H
#define _BALLTRACK_OBJLOADER_H

#include <vector>
#include <string>
#include "Drawables/Model3D.h"

namespace BallTrack
{
    class ObjLoader
    {
    public:
        std::vector<Model3D> loadObjFile(std::string path);
    };
}

#endif //_BALLTRACK_OBJLOADER_H