#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include <vector>
#include <GL/glew.h>

#include "../Entity.h"
#include "../Glm_Common.h"

namespace World
{
    class Terrain : public Entity
    {
    public:
        Terrain(int rows, int columns, float size, Vector3 pos);
        ~Terrain();

        void bind() const;
        void unbind() const;
        GLuint getIndicesCount() const;

        std::vector<Vector3> m_treePositions;
    private:
        void addVBO(int dim, const std::vector<GLfloat>& data);
        void addEBO(const std::vector<GLuint>& indices);
        void setVertexPositions();
        void setIndices();
        void setNormals();
        void generateHeightsUsingAverages();
        void generateHeightsUsingPerlin();
        Vector3 calcNormal(GLuint i1, GLuint i2, GLuint i3);

        std::vector<GLuint> m_buffers;
        std::vector<GLfloat> m_vertexPositions;
        std::vector<GLuint> m_indices;
        std::vector<GLfloat> m_textureCoords;
        std::vector<GLfloat> m_normals;
        std::vector<GLfloat> m_heights;
        GLuint m_vao;
        GLuint m_vboCount = 0;
        GLuint m_indicesCount = 0;
        int m_rows = 0;
        int m_columns = 0;
        float m_size = 0;
        float m_mountainHeight = 0.5f;
    };
}

#endif // TERRAIN_H_INCLUDED
