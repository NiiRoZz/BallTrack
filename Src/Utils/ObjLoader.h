#ifndef _BALLTRACK_OBJLOADER_H
#define _BALLTRACK_OBJLOADER_H

#include <vector>
#include <string>
#include "Drawables/Model3D.h"
#include "Entities/PhysicEntity.h"
#include "Physics/SphereCollisionPrimitive.h"
#include "Physics/RectangleCollisionPrimitive.h"

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
        static PhysicEntity loadEntity(const std::string& path, const std::string& fileName);

        static Model3D loadObjFile(const std::string& path, const std::string& fileName);
        static PhysicEntity loadBtFile(const std::string& path, const std::string& fileName, Model3D& model);

    private:
        static std::vector<std::string> split(const std::string& s, const std::string& delimiter);

        static void ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
        static void rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
        static void trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
    };
}

#endif //_BALLTRACK_OBJLOADER_H