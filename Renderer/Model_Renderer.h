#ifndef MODEL_RENDERER_H_INCLUDED
#define MODEL_RENDERER_H_INCLUDED

#include <vector>

#include "../Models/Model.h"
#include "../Shaders/Model_Shader.h"
#include "../Glm_Common.h"
#include "../Camera.h"

namespace Renderer
{
    class Model_Renderer
    {
    public:
        void draw(const Model& model);
        void update(const Camera& camera, Vector3 lightPos, Vector4 plane);
    private:
        std::vector<const Model*> m_models;
        Shader::Model_Shader m_shader;
    };
}

#endif // MODEL_RENDERER_H_INCLUDED
