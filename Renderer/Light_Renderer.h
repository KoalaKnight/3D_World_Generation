#ifndef LIGHT_RENDERER_H_INCLUDED
#define LIGHT_RENDERER_H_INCLUDED

#include <vector>
#include "../World/Light.h"
#include "../Camera.h"
#include "../Shaders/Light_Shader.h"

namespace Renderer
{
    class Light_Renderer
    {
    public:
        void draw(const World::Light& light);
        void update(const Camera& camera, Vector4 plane);
    private:
        std::vector<const World::Light*> m_lights;
        Shader::Light_Shader m_shader;
    };
}

#endif // LIGHT_RENDERER_H_INCLUDED
