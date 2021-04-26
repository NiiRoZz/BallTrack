#ifndef _BALLTRACK_OBJLOADER_H
#define _BALLTRACK_OBJLOADER_H

#if defined(WIN32) || defined(WIN64)
    #define NOMINMAX
#endif

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

        static std::unique_ptr<PhysicEntity> loadEntity(const std::string& path, const std::string& fileName);

        static Model3D loadObjFile(const std::string& path, const std::string& fileName);
        static std::unique_ptr<PhysicEntity> loadBtFile(const std::string& path, const std::string& fileName, Model3D& model);

    private:
        static std::vector<std::string> split(const std::string& s, const std::string& delimiter);

        static void ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
        static void rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
        static void trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
    };
}

#endif //_BALLTRACK_OBJLOADER_H