#include "Water.h"

namespace World
{
    Water::Water(float size, Vector3 pos)
    {
        this->position = pos;
        m_vertexPositions =
        {
            pos.x, pos.y, pos.z,
            pos.x + size, pos.y, pos.z,
            pos.x + size, pos.y, pos.z + size,
            pos.x, pos.y, pos.z + size
        };
        m_indices =
        {
          0, 1, 3,
          2, 1, 3
        };
        m_normals =
        {
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        };
        m_textureCoords =
        {
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
            0.0, 1.0
        };
        m_indicesCount = 6;
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        addVBO(3, m_vertexPositions);
        addVBO(3, m_normals);
        addVBO(2, m_textureCoords);
        addEBO(m_indices);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Water::~Water()
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(m_buffers.size(), m_buffers.data());
    }

    void Water::bind() const
    {
        glBindVertexArray(m_vao);
    }

    void Water::unbind() const
    {
        glBindVertexArray(0);
    }

    GLuint Water::getIndicesCount() const
    {
        return m_indicesCount;
    }

    void Water::addVBO(int dim, const std::vector<GLfloat>& data)
    {
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,
                     data.size() * sizeof(data[0]),
                     data.data(),
                     GL_STATIC_DRAW);
        glVertexAttribPointer(m_vboCount,
                              dim,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (GLvoid*) 0);

        glEnableVertexAttribArray(m_vboCount++);

        m_buffers.push_back(vbo);
    }

    void Water::addEBO(const std::vector<GLuint>& indices)
    {
        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     indices.size() * sizeof (indices[0]),
                     indices.data(),
                     GL_STATIC_DRAW);
        m_buffers.push_back(ebo);
    }
}
