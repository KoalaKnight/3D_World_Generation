#include "Model.h"

//#include <iostream>

Model::Model(std::string fileName, Vector3 pos, float scale)
{
    this->position = pos;
    objLoader.load(fileName);
    m_indicesCount = objLoader.m_indices.size();
    for(int i = 0; i < objLoader.m_vertexPositions.size(); i++)
    {
        objLoader.m_vertexPositions[i] *= scale;
    }

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    addVBO(3, objLoader.m_vertexPositions);
    addVBO(3, objLoader.m_normals);
    addVBO(3, objLoader.m_colours);
    addEBO(objLoader.m_indices);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /*std::cout << "***VERTEX POSITIONS***" << std::endl << std::endl;

    for(int i = 0; i < objLoader.m_vertexPositions.size(); i += 3)
    {
        std::cout << objLoader.m_vertexPositions[i] << ", " << objLoader.m_vertexPositions[i + 1] << ", " << objLoader.m_vertexPositions[i + 2] << std::endl;
    }

    std::cout << "***INDICES***" << std::endl << std::endl;

    for(int i = 0; i < objLoader.m_indices.size(); i++)
    {
        std::cout << objLoader.m_indices[i] << std::endl;
    }*/
}

Model::~Model()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(m_buffers.size(), m_buffers.data());
}

void Model::bind() const
{
    glBindVertexArray(m_vao);
}

void Model::unbind() const
{
    glBindVertexArray(0);
}

GLuint Model::getIndicesCount() const
{
    return m_indicesCount;
}

void Model::addVBO(int dim, const std::vector<GLfloat>& data)
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

void Model::addEBO(const std::vector<GLuint>& indices)
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

void Model::setPosition(Vector3 vec)
{
    this->position = vec;
}
