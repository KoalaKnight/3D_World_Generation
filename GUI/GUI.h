#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <vector>
#include <GL/glew.h>

#include "../Glm_Common.h"

namespace GUI
{
    class GUI
    {
    public:
        GUI(float size, Vector2 pos);
        ~GUI();

        void bind() const;
        void unbind() const;
        GLuint getIndicesCount() const;
    private:
        void addVBO(int dim, const std::vector<GLfloat>& data);
        void addEBO(const std::vector<GLuint>& indices);

        std::vector<GLuint> m_buffers;
        std::vector<GLfloat> m_vertexPositions;
        std::vector<GLuint> m_indices;
        std::vector<GLfloat> m_textureCoords;

        GLuint m_vao;
        GLuint m_vboCount = 0;
        GLuint m_indicesCount = 0;
    };
}

#endif // GUI_H_INCLUDED
