#include "GUI.h"

namespace GUI
{
    GUI::GUI(float size, Vector2 pos)
    {
        m_vertexPositions =
        {
            pos.x, pos.y,
            pos.x + size, pos.y,
            pos.x + size, pos.y + size,
            pos.x, pos.y + size
        };
        m_textureCoords =
        {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
        };
        m_indices =
        {
          0, 1, 2,
          0, 3, 2
        };
        m_indicesCount = 6;
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        addVBO(2, m_vertexPositions);
        addVBO(2, m_textureCoords);
        addEBO(m_indices);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    GUI::~GUI()
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(m_buffers.size(), m_buffers.data());
    }

    void GUI::bind() const
    {
        glBindVertexArray(m_vao);
    }

    void GUI::unbind() const
    {
        glBindVertexArray(0);
    }

    GLuint GUI::getIndicesCount() const
    {
        return m_indicesCount;
    }

    void GUI::addVBO(int dim, const std::vector<GLfloat>& data)
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

    void GUI::addEBO(const std::vector<GLuint>& indices)
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
