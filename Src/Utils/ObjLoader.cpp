#include "ObjLoader.h"

#include <fstream>
#include <string>
#include <iostream>

namespace BallTrack
{
    static std::vector<Model3D> ObjLoader::loadObjFile(std::string path)
    {
        std::vector<Model3D> models;

        std::ifstream fs;
        fs.open(path);

        if (!fs.is_open()) return models;

        std::cout << "opened " << path << std::endl;

        std::string line;
        while ( std::getline(fs, line) )
        {
            std::cout << line << '\n';
        }

        fs.close();
        return models;
    }
}