#ifndef WATER_H_INCLUDED
#define WATER_H_INCLUDED

#include <vector>
#include <GL/glew.h>

#include "../Entity.h"
#include "../Glm_Common.h"

namespace World
{
    class Water : public Entity
    {
    public:
        Water(float size, Vector3 pos);
        ~Water();

        void bind() const;
        void unbind() const;
        GLuint getIndicesCount() const;
    private:
        void addVBO(int dim, const std::vector<GLfloat>& data);
        void addEBO(const std::vector<GLuint>& indices);

        std::vector<GLuint> m_buffers;
        std::vector<GLfloat> m_vertexPositions;
        std::vector<GLfloat> m_textureCoords;
        std::vector<GLuint> m_indices;
        std::vector<GLfloat> m_normals;
        GLuint m_vao;
        GLuint m_vboCount = 0;
        GLuint m_indicesCount = 0;
    };
}

#endif // WATER_H_INCLUDED
