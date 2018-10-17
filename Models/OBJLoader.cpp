#include "OBJLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>

#include "../Glm_Common.h"

void OBJLoader::load(std::string fileName)
{
    loadMaterials(fileName);
    std::ifstream inFile ("Data/Models/" + fileName + ".obj");
    std::string line;
    std::stringstream stringStream;
    if (!inFile.is_open())
    {
        throw std::runtime_error ("Could not open file: " + fileName);
    }

    int currentMaterial = 0;

    while(std::getline(inFile, line))
    {
        if(line.substr(0, 2) == "v ")
        {
            line = line.substr(line.find(" ") + 1);
            m_tempVertexPositions.push_back(atof(line.substr(0, line.find(" ")).c_str()));
            line = line.substr(line.find(" ") + 1);
            m_tempVertexPositions.push_back(atof(line.substr(0, line.find(" ")).c_str()));
            line = line.substr(line.find(" ") + 1);
            m_tempVertexPositions.push_back(atof(line.c_str()));
        }
        else if(line.substr(0, 2) == "vt")
        {
            line = line.substr(line.find(" ") + 1);
            m_tempTextureCoords.push_back(atof(line.substr(0, line.find(" ")).c_str()));
            line = line.substr(line.find(" ") + 1);
            m_tempTextureCoords.push_back(atof(line.c_str()));
        }
        else if(line.substr(0, 2) == "vn")
        {
            line = line.substr(line.find(" ") + 1);
            m_tempNormals.push_back(atof(line.substr(0, line.find(" ")).c_str()));
            line = line.substr(line.find(" ") + 1);
            m_tempNormals.push_back(atof(line.substr(0, line.find(" ")).c_str()));
            line = line.substr(line.find(" ") + 1);
            m_tempNormals.push_back(atof(line.c_str()));
        }
        else if(line.substr(0, 2) == "f ")
        {
            //Does not currently deal with texture coords
            for(int i = 0; i < 3; i ++)
            {
                line = line.substr(line.find(" ") + 1);
                int vi = atoi(line.substr(0, line.find("//")).c_str()) - 1;
                m_vertexPositions.push_back(m_tempVertexPositions[3 * vi]);
                m_vertexPositions.push_back(m_tempVertexPositions[(3 * vi) + 1]);
                m_vertexPositions.push_back(m_tempVertexPositions[(3 * vi) + 2]);
                line = line.substr(line.find("//") + 2);
                int ni = atoi(line.substr(0, line.find(" ")).c_str()) - 1;
                m_normals.push_back(m_tempNormals[3 * ni]);
                m_normals.push_back(m_tempNormals[(3 * ni) + 1]);
                m_normals.push_back(m_tempNormals[(3 * ni) + 2]);
                m_tempcolours.push_back(m_materials[currentMaterial].r);
                m_tempcolours.push_back(m_materials[currentMaterial].g);
                m_tempcolours.push_back(m_materials[currentMaterial].b);
            }
        }
        else if(line.substr(0, 6) == "usemtl")
        {
            line = line.substr(line.find(" ") + 1);
            for(int i = 0; i < m_materials.size(); i++)
            {
                if(m_materials[i].name == line)
                {
                    currentMaterial = i;
                    break;
                }
            }
        }
    }
    m_tempVertexPositions.clear();
    m_tempTextureCoords.clear();
    m_tempNormals.clear();
    setIndices();
    normalizeNormals();
}

void OBJLoader::setIndices()
{
    int count = 0;
    for(int i = 0; i < m_vertexPositions.size(); i += 3)
    {
        int index = findSame(m_vertexPositions[i], m_vertexPositions[i + 1], m_vertexPositions[i + 2], m_tempcolours[i], m_tempcolours[i + 1], m_tempcolours[i + 2]);
        if(index == -1)
        {
            m_tempVertexPositions.push_back(m_vertexPositions[i]);
            m_tempVertexPositions.push_back(m_vertexPositions[i + 1]);
            m_tempVertexPositions.push_back(m_vertexPositions[i + 2]);
            m_tempNormals.push_back(m_normals[i]);
            m_tempNormals.push_back(m_normals[i + 1]);
            m_tempNormals.push_back(m_normals[i + 2]);
            m_colours.push_back(m_tempcolours[i]);
            m_colours.push_back(m_tempcolours[i + 1]);
            m_colours.push_back(m_tempcolours[i + 2]);
            m_indices.push_back(count++);
        }
        else
        {
            //m_tempNormals[index] += m_normals[i];
            //m_tempNormals[index + 1] += m_normals[i + 1];
            //m_tempNormals[index + 2] += m_normals[i + 2];
            m_indices.push_back(index);
        }
    }
    m_vertexPositions = m_tempVertexPositions;
    m_normals = m_tempNormals;
    m_tempVertexPositions.clear();
    m_tempNormals.clear();
    m_tempcolours.clear();
}


int OBJLoader::findSame(float x, float y, float z, float r, float g, float b)
{
    if(m_tempVertexPositions.size() == 0)
    {
        return -1;
    }
    for(int i = 0; i < m_tempVertexPositions.size(); i += 3)
    {
        if(isSame(m_tempVertexPositions[i], x) && isSame(m_tempVertexPositions[i + 1], y) && isSame(m_tempVertexPositions[i + 2], z)
           && isSame(m_tempcolours[i], r) && isSame(m_tempcolours[i + 1], g) && isSame(m_tempcolours[i + 2], b))
        {
            return (i / 3);
        }
    }
    return -1;
}

bool OBJLoader::isSame(float a, float b)
{
    if(-0.000001 < (a - b) &&  (a - b) < 0.000001)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void OBJLoader::normalizeNormals()
{
    for(int i = 0; i < m_normals.size(); i += 3)
    {
        Vector3 n = Vector3(m_normals[i], m_normals[i + 1], m_normals[i + 2]);
        n = glm::normalize(n);
        m_normals[i] = n.x;
        m_normals[i + 1] = n.y;
        m_normals[i + 2] = n.z;
    }
}

void OBJLoader::loadMaterials(std::string fileName)
{
    std::ifstream inFile ("Data/Models/" + fileName + ".mtl");
    std::string line;
    std::stringstream stringStream;
    if (!inFile.is_open())
    {
        throw std::runtime_error ("Could not open file: " + fileName);
    }

    Material m;

    while(std::getline(inFile, line))
    {
        if(line.substr(0, 6) == "newmtl")
        {
            line = line.substr(line.find(" ") + 1);
            m.name = line;

        }
        else if(line.substr(0, 2) == "Kd")
        {
            line = line.substr(line.find(" ") + 1);
            m.r = atof(line.substr(0, line.find(" ")).c_str());
            line = line.substr(line.find(" ") + 1);
            m.g = atof(line.substr(0, line.find(" ")).c_str());
            line = line.substr(line.find(" ") + 1);
            m.b = atof(line.c_str());
            m_materials.push_back(m);
        }
    }
}
