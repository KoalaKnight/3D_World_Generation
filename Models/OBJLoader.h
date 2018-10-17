#ifndef OBJLOADER_H_INCLUDED
#define OBJLOADER_H_INCLUDED

#include <string>
#include <vector>
#include <GL/glew.h>

struct Material
{
    std::string name;
    float r, g, b;
};

class OBJLoader
{
public:
    void load(std::string fileName);

    std::vector<GLfloat> m_vertexPositions;
    std::vector<GLfloat> m_textureCoords;
    std::vector<GLfloat> m_normals;
    std::vector<GLfloat> m_colours;
    std::vector<GLuint> m_indices;
private:
    int findSame(float x, float y, float z, float r, float g, float b);
    bool isSame(float a, float b);
    void setIndices();
    void normalizeNormals();
    void loadMaterials(std::string fileName);

    std::vector<GLfloat> m_tempVertexPositions;
    std::vector<GLfloat> m_tempTextureCoords;
    std::vector<GLfloat> m_tempNormals;
    std::vector<GLfloat> m_tempcolours;
    std::vector<Material> m_materials;
};

#endif // OBJLOADER_H_INCLUDED
