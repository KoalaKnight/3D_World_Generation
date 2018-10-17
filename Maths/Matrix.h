#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "../Glm_Common.h"

class Camera;

struct Entity;

namespace Maths
{
    Matrix4 createViewMatrix(const Camera& entity);
    Matrix4 createModelMatrix(const Entity& entity);
    Matrix4 createProjMatrix();
}

#endif // MATRIX_H_INCLUDED
