#include "ObjLoader.h"

#include <fstream>
#include <string>
#include <iostream>

namespace BallTrack
{
    std::vector<Model3D> ObjLoader::loadObjFile(const std::string& path, const std::string& fileName)
    {
        std::vector<Model3D> models;

        std::string objPath = path + fileName + ".obj";

        std::ifstream fs;
        fs.open(objPath);

        if (!fs.is_open()) return models;

        std::cout << "opened " << objPath << std::endl;

        std::string line;
        while ( std::getline(fs, line) )
        {
            if (line.size() <= 0 || line[0] == '#')
            {
                continue;
            }

            std::cout << line << '\n';
        }

        fs.close();
        return models;
    }
}