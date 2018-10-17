#ifndef MULTIPLE_MODELS_RENDERER_H_INCLUDED
#define MULTIPLE_MODELS_RENDERER_H_INCLUDED

#include <vector>

#include "../Models/Multiple_Models.h"
#include "../Shaders/Model_Shader.h"
#include "../Glm_Common.h"
#include "../Camera.h"

namespace Renderer
{
    class Multiple_Models_Renderer
    {
    public:
        void draw( Multiple_Models& multipleModels);
        void update(const Camera& camera, Vector3 lightPos, Vector4 plane);
    private:
        std::vector<Multiple_Models*> m_multipleModels;
        Shader::Model_Shader m_shader;
    };
}

#endif // MULTIPLE_MODELS_RENDERER_H_INCLUDED
