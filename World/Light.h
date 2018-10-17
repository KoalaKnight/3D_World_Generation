#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include <vector>
#include <GL/glew.h>

#include "../Entity.h"
#include "../Glm_Common.h"

namespace World
{
    class Light : public Entity
    {
    public:
        Light(Vector3 pos);
        ~Light();

        void bind() const;
        void unbind() const;
        GLuint getIndicesCount() const;
    private:
        void addVBO(int dim, const std::vector<GLfloat>& data);
        void addEBO(const std::vector<GLuint>& indices);
        void setVertexPositions();
        void setIndices();

        std::vector<GLuint> m_buffers;
        std::vector<GLfloat> m_vertexPositions;
        std::vector<GLuint> m_indices;

        GLuint m_vao;
        GLuint m_vboCount = 0;
        GLuint m_indicesCount = 0;
        float m_size = 0.5f;
    };
}

#endif // LIGHT_H_INCLUDED
