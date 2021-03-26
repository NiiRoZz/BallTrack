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
        
        std::vector<Pos3D> positions;
        std::vector<Dir3D> normals;
        std::vector<Vector2> uvs;

        std::vector<Triangle> triangles;

        while ( std::getline(fs, line) )
        {
            if (line.size() <= 0)
            {
                continue;
            }

            //Remove any whitespace
            trim(line);

            if (line[0] == '#')
            {
                continue;
            }

            std::cout << line << '\n';

            std::vector<std::string> tokens = split(line, " ");

            if (tokens.size() <= 0)
            {
                continue;
            }

            if (tokens[0] == "o")
            {
                if (!triangles.empty())
                {
                    models.emplace_back(triangles);
                }

                triangles.clear();
            }
            else if (tokens[0] == "v")
            {
                if (tokens.size() < 4)
                {
                    continue;
                }

                positions.emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));

                //std::cout << "v x : " << std::stof(tokens[1]) << " y : " << std::stof(tokens[2]) << " z : " << std::stof(tokens[3]) << std::endl;
            }
            else if (tokens[0] == "vt")
            {
                if (tokens.size() < 3)
                {
                    continue;
                }

                uvs.emplace_back(std::stof(tokens[1]), std::stof(tokens[2]));
                //std::cout << "vt x : " << std::stof(tokens[1]) << " y : " << std::stof(tokens[2]) << std::endl;
            }
            else if (tokens[0] == "vn")
            {
                if (tokens.size() < 4)
                {
                    continue;
                }

                normals.emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));

                //std::cout << "vn x : " << std::stof(tokens[1]) << " y : " << std::stof(tokens[2]) << " z : " << std::stof(tokens[3]) << std::endl;
            }
            else if (tokens[0] == "f")
            {
                if (tokens.size() < 4)
                {
                    continue;
                }

                std::vector<Vertex> vertices;

                for (std::size_t i = 1; i < tokens.size(); ++i)
                {
                    std::vector<std::string> indices = split(tokens[i], "/");

                    Vertex vertex;

                    switch (indices.size())
                    {
                        case 1:
                        {
                            vertex.position = positions[std::stoi(indices[0]) - 1];
                            break;
                        }

                        case 2:
                        {
                            vertex.position = positions[std::stoi(indices[0]) - 1];
                            vertex.uv = uvs[std::stoi(indices[1])];
                            break;
                        }

                        case 3:
                        {
                            vertex.position = positions[std::stoi(indices[0]) - 1];

                            if (indices[1].size() > 0)
                            {
                                vertex.uv = uvs[std::stoi(indices[1]) - 1];
                            }
                            
                            vertex.normal = normals[std::stoi(indices[2]) - 1];
                            break;
                        }
                    }

                    /*std::cout << "position : " << vertex.position.x << " " << vertex.position.y << " " << vertex.position.z << std::endl;
                    std::cout << "normal : " << vertex.normal.x << " " << vertex.normal.y << " " << vertex.normal.z << std::endl;
                    std::cout << "uv : " << vertex.uv.x << " " << vertex.uv.y << std::endl;*/

                    vertices.push_back( std::move(vertex) );
                }

                triangles.emplace_back(vertices);
            }
        }

        if (!triangles.empty())
        {
            models.emplace_back(triangles);
        }

        fs.close();
        return models;
    }

    std::vector<std::string> ObjLoader::split(const std::string& s, const std::string& delimiter)
    {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos)
        {
            token = s.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }

        res.push_back(s.substr(pos_start));
        return res;
    }

    void ObjLoader::ltrim(std::string& str, const std::string& chars)
    {
        str.erase(0, str.find_first_not_of(chars));
    }

    void ObjLoader::rtrim(std::string& str, const std::string& chars)
    {
        str.erase(str.find_last_not_of(chars) + 1);
    }

    void ObjLoader::trim(std::string& str, const std::string& chars)
    {
        rtrim(str, chars);
        ltrim(str, chars);
    }
}