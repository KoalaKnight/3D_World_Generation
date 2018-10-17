#include "Terrain.h"

#include "../Util/Random.h"
#include "../FastNoise/FastNoise.h"

namespace World
{
    Terrain::Terrain(int rows, int columns, float size, Vector3 pos)
    :   m_rows(rows + 1)
    ,   m_columns(columns + 1)
    ,   m_size(size)
    {
        this->position = pos;
        //generateHeightsUsingAverages();
        generateHeightsUsingPerlin();
        setVertexPositions();
        setIndices();
        setNormals();

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        addVBO(3, m_vertexPositions);
        addVBO(3, m_normals);
        addVBO(2, m_textureCoords);
        addEBO(m_indices);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Terrain::~Terrain()
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(m_buffers.size(), m_buffers.data());
    }

    void Terrain::bind() const
    {
        glBindVertexArray(m_vao);
    }

    void Terrain::unbind() const
    {
        glBindVertexArray(0);
    }

    GLuint Terrain::getIndicesCount() const
    {
        return m_indicesCount;
    }

    void Terrain::addVBO(int dim, const std::vector<GLfloat>& data)
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

    void Terrain::addEBO(const std::vector<GLuint>& indices)
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

    void Terrain::generateHeightsUsingPerlin()
    {
        Random::init();
        FastNoise noise;
        noise.SetNoiseType(FastNoise::Perlin);
        noise.SetSeed(Random::intInRange(0, 1000));
        noise.SetFrequency(0.4 * m_size);
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_columns; j++)
            {
                float a = noise.GetNoise(i, j);
                m_heights.push_back(a*a*2);
            }
        }
    }

    void Terrain::generateHeightsUsingAverages()
    {
        Random::init();
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_columns; j++)
            {
                m_heights.push_back(Random::floatInRange(0.0f, 5.0f));
            }
        }

        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_columns; j++)
            {
                int count = 1;
                GLuint startIndex = j + (i * m_columns);
                float total = m_heights[startIndex];
                if(j > 0)
                {
                    total += m_heights[startIndex - 1];
                    count++;
                }
                if(j < m_columns - 1)
                {
                    total += m_heights[startIndex + 1];
                    count++;
                }
                if(i > 0)
                {
                    total += m_heights[startIndex - m_columns];
                    count++;
                }
                if(i < m_rows - 1)
                {
                    total += m_heights[startIndex + m_columns];
                    count++;
                }
                if(j > 0 && i > 0)
                {
                    total += m_heights[startIndex - m_columns - 1];
                    count++;
                }
                if(j < m_columns - 1 && i < m_rows - 1)
                {
                    total += m_heights[startIndex + m_columns + 1];
                    count++;
                }
                if(j > 0 && i < m_rows - 1)
                {
                    total += m_heights[startIndex + m_columns - 1];
                    count++;
                }
                if(j < m_columns - 1 && i > 0)
                {
                    total += m_heights[startIndex - m_columns + 1];
                    count++;
                }
                m_heights[startIndex] = total / (float)count;
            }
        }

        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_columns; j++)
            {
                GLuint startIndex = j + (i * m_columns);
                m_heights[startIndex] *= m_size;
            }
        }
    }


    void Terrain::setVertexPositions()
    {
        int count = 0;
        FastNoise noise;
        noise.SetNoiseType(FastNoise::Perlin);
        noise.SetSeed(Random::intInRange(0, 1000));
        noise.SetFrequency(0.4 * m_size);

        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_columns; j++)
            {
                m_vertexPositions.push_back(this->position.x + (m_size * j));
                m_vertexPositions.push_back(this->position.y + m_heights[count]);
                m_vertexPositions.push_back(this->position.z + (m_size * i));
                if(noise.GetNoise(i, j) > 0.5 && m_heights[j + (i * m_columns)] > 0.05 && m_heights[j + (i * m_columns)] < m_mountainHeight)
                {
                    m_treePositions.push_back(Vector3(this->position.x + (m_size * j), this->position.y + m_heights[count] - 2.01, this->position.z + (m_size * i)));
                }
                if(j % 2 == 0)
                {
                    if(m_heights[j + (i * m_columns)] > m_mountainHeight)
                    {
                        m_textureCoords.push_back(0.0f);
                    }
                    else
                    {
                        m_textureCoords.push_back(0.5f);
                    }
                }
                else
                {
                    if(m_heights[j + (i * m_columns)] > m_mountainHeight)
                    {
                        m_textureCoords.push_back(0.5f);
                    }
                    else
                    {
                        m_textureCoords.push_back(1.0f);
                    }
                }

                if(i % 2 == 0)
                {
                    if(m_heights[j + (i * m_columns)] < 0.05f)
                    {
                        m_textureCoords.push_back(0.5f);
                    }
                    else if(m_heights[j + (i * m_columns)] > m_mountainHeight)
                    {
                        m_textureCoords.push_back(0.5f);
                    }
                    else
                    {
                        m_textureCoords.push_back(0.0f);
                    }
                }
                else
                {
                    if(m_heights[j + (i * m_columns)] < 0.05f)
                    {
                        m_textureCoords.push_back(1.0f);
                    }
                    else if(m_heights[j + (i * m_columns)] > m_mountainHeight)
                    {
                        m_textureCoords.push_back(1.0f);
                    }
                    else
                    {
                        m_textureCoords.push_back(0.5f);
                    }
                }
                count++;
            }
        }
    }

    void Terrain::setIndices()
    {
        for(int i = 0; i < m_rows - 1; i++)
        {
            for(int j = 0; j < m_columns - 1; j ++)
            {
                GLuint startIndex = j + (i * m_columns);
                m_indices.push_back(startIndex);
                m_indices.push_back(startIndex + 1);
                m_indices.push_back(startIndex + m_columns);
                m_indices.push_back(startIndex + m_columns);
                m_indices.push_back(startIndex + m_columns + 1);
                m_indices.push_back(startIndex + 1);
                m_indicesCount += 6;
            }
        }
    }

    void Terrain::setNormals()
    {
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_columns; j++)
            {
                //If vertex is on corner with only 1 triangle
                if((i == 0 && j == 0) || (i == m_rows - 1 && j == m_columns - 1))
                {
                    GLuint i1 = j + (i * m_columns);
                    GLuint i2, i3;

                    if(i == 0)
                    {
                        i2 = i1 + 1;
                        i3 = i1 + m_columns;
                    }
                    else
                    {
                        i2 = i1 - 1;
                        i3 = i1 - m_columns;
                    }

                    Vector3 n1 = calcNormal(i1, i2, i3);
                    m_normals.push_back(n1.x);
                    m_normals.push_back(n1.y);
                    m_normals.push_back(n1.z);
                }
                //If vertex is on corner with 2 triangles
                else if((i == 0 && j == m_columns - 1) || (i == m_rows - 1 && j == 0))
                {
                    Vector3 n1, n2;
                    GLuint i1 = j + (i * m_columns);
                    GLuint i2, i3;
                    if(i == 0)
                    {
                        i2 = i1 - 1;
                        i3 = i2 + m_columns;
                        n1 = calcNormal(i1, i2, i3);
                        i2 = i1 + m_columns;
                        n2 = calcNormal(i1, i2, i3);
                    }
                    else
                    {
                        i2 = i1 - m_columns;
                        i3 = i2 + 1;
                        n1 = calcNormal(i1, i2, i3);
                        i2 = i1 + 1;
                        n2 = calcNormal(i1, i2, i3);
                    }

                    n1 = glm::normalize(n1 + n2);
                    m_normals.push_back(n1.x);
                    m_normals.push_back(n1.y);
                    m_normals.push_back(n1.z);
                }
                //If vertex is on edge
                else if(i == 0 || i == m_rows - 1 || j == 0 || j == m_columns - 1)
                {
                    Vector3 n1, n2, n3;
                    GLuint i1 = j + (i * m_columns);
                    GLuint i2, i3;
                    //Bottom edge
                    if(i == 0)
                    {
                        i2 = i1 - 1;
                        i3 = i2 + m_columns;
                        n1 = calcNormal(i1, i2, i3);
                        i2 = i1 + m_columns;
                        n2 = calcNormal(i1, i2, i3);
                        i3 = i1 + 1;
                        n3 = calcNormal(i1, i2, i3);
                    }
                    //Top edge
                    else if(i == m_rows - 1)
                    {
                        i2 = i1 - 1;
                        i3 = i1 - m_columns;
                        n1 = calcNormal(i1, i2, i3);
                        i2 = i1 - m_columns + 1;
                        n2 = calcNormal(i1, i2, i3);
                        i3 = i1 + 1;
                        n3 = calcNormal(i1, i2, i3);
                    }
                    //Left edge
                    else if(j == 0)
                    {
                        i2 = i1 - m_columns;
                        i3 = i2 + 1;
                        n1 = calcNormal(i1, i2, i3);
                        i2 = i1 + 1;
                        n2 = calcNormal(i1, i2, i3);
                        i3 = i1 + m_columns;
                        n3 = calcNormal(i1, i2, i3);
                    }
                    //Right edge
                    else
                    {
                        i2 = i1 - m_columns;
                        i3 = i1 - 1;
                        n1 = calcNormal(i1, i2, i3);
                        i2 = i3 + m_columns;
                        n2 = calcNormal(i1, i2, i3);
                        i3 = i1 + m_columns;
                        n3 = calcNormal(i1, i2, i3);
                    }

                    n1 = glm::normalize(n1 + n2 + n3);
                    m_normals.push_back(n1.x);
                    m_normals.push_back(n1.y);
                    m_normals.push_back(n1.z);
                }
                //If vertex is surrounded by vertices
                else
                {
                    Vector3 n1, n2, n3, n4, n5, n6;
                    GLuint i1 = j + (i * m_columns);
                    GLuint i2, i3;

                    i2 = i1 - 1;
                    i3 = i2 + m_columns;
                    n1 = calcNormal(i1, i2, i3);
                    i2 = i1 + m_columns;
                    n2 = calcNormal(i1, i2, i3);
                    i3 = i1 + 1;
                    n3 = calcNormal(i1, i2, i3);
                    i2 = i3 - m_columns;
                    n4 = calcNormal(i1, i2, i3);
                    i3 = i1 - m_columns;
                    n5 = calcNormal(i1, i2, i3);
                    i2 = i1 - 1;
                    n6 = calcNormal(i1, i2, i3);

                    n1 = glm::normalize(n1 + n2 + n3 + n4 + n5 + n6);
                    m_normals.push_back(n1.x);
                    m_normals.push_back(n1.y);
                    m_normals.push_back(n1.z);
                }
            }
        }
    }

    Vector3 Terrain::calcNormal(GLuint i1, GLuint i2, GLuint i3)
    {
        Vector3 v1 = Vector3(m_vertexPositions[i1 * 3], m_vertexPositions[(i1 * 3) + 1], m_vertexPositions[(i1 * 3) + 2]);
        Vector3 v2 = Vector3(m_vertexPositions[i2 * 3], m_vertexPositions[(i2 * 3) + 1], m_vertexPositions[(i2 * 3) + 2]);
        Vector3 v3 = Vector3(m_vertexPositions[i3 * 3], m_vertexPositions[(i3 * 3) + 1], m_vertexPositions[(i3 * 3) + 2]);
        v1 = glm::normalize(glm::cross(v2 - v1, v3 - v1));
        if(v1.y < 0)
        {
            v1 *= -1;
        }
        return v1;
    }
}
