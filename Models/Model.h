#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <vector>
#include <GL/glew.h>

#include "OBJLoader.h"
#include "../Entity.h"
#include "../Glm_Common.h"

class Model : public Entity
{
public:
    Model(std::string fileName, Vector3 pos, float scale);
    ~Model();

    void bind() const;
    void unbind() const;
    GLuint getIndicesCount() const;

    void setPosition(Vector3 vec);
private:
    void addVBO(int dim, const std::vector<GLfloat>& data);
    void addEBO(const std::vector<GLuint>& indices);

    std::vector<GLuint> m_buffers;
    GLuint m_vao;
    GLuint m_vboCount = 0;
    GLuint m_indicesCount = 0;
    OBJLoader objLoader;
};

#endif // MODEL_H_INCLUDED
