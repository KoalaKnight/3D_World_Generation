#include "Light.h"

namespace World
{
    Light::Light(Vector3 pos)
    {
        this->position = pos;
        setVertexPositions();
        setIndices();

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        addVBO(3, m_vertexPositions);
        addEBO(m_indices);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Light::~Light()
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(m_buffers.size(), m_buffers.data());
    }

    void Light::bind() const
    {
        glBindVertexArray(m_vao);
    }

    void Light::unbind() const
    {
        glBindVertexArray(0);
    }

    GLuint Light::getIndicesCount() const
    {
        return m_indicesCount;
    }

    void Light::addVBO(int dim, const std::vector<GLfloat>& data)
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

    void Light::addEBO(const std::vector<GLuint>& indices)
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

    void Light::setVertexPositions()
    {
        m_vertexPositions =
        {
            //Base
            0.0f, 0.0f, 0.0f,
            m_size, 0.0f, 0.0f,
            m_size, 0.0f, m_size,
            0.0f, 0.0f, m_size,
            //Top
            0.0f, m_size, 0.0f,
            m_size, m_size, 0.0f,
            m_size, m_size, m_size,
            0.0f, m_size, m_size,
        };
    }

    void Light::setIndices()
    {
        m_indices =
        {
            //Base
            0, 1, 2,
            0, 3, 2,
            //Front
            0, 4, 1,
            4, 5, 1,
            //Left Side
            0, 4, 3,
            4, 7, 3,
            //Back
            3, 7, 2,
            7, 6, 2,
            //Right Side
            2, 6, 1,
            6, 5, 1,
            //Top
            4, 5, 6,
            4, 7, 6
        };
        m_indicesCount = 36;
    }
}
