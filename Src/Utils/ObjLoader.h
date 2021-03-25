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
        /**
         * @brief Load a .obj file
         *
         * It is used to load .obj file. It will try to load the .bt file corresponding to the .obj file
         * 
         * @param path Path to the obj file with a '/' at the end of the path
         * @param fileName file name without the .obj format at the end
         */
        std::vector<Model3D> loadObjFile(const std::string& path, const std::string& fileName);
    };
}

#endif //_BALLTRACK_OBJLOADER_H