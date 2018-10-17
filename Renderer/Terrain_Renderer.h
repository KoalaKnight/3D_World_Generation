#ifndef TERRAIN_RENDERER_H_INCLUDED
#define TERRAIN_RENDERER_H_INCLUDED

#include <vector>
#include "../World/Terrain.h"
#include "../Camera.h"
#include "../Shaders/Terrain_Shader.h"
#include "../Glm_Common.h"
#include "../Texture/Texture.h"

namespace Renderer
{
    class Terrain_Renderer
    {
    public:
        Terrain_Renderer();

        void draw(const World::Terrain& terrain);
        void update(const Camera& camera, Vector3 lightPos, Vector4 plane);
    private:
        std::vector<const World::Terrain*> m_terrains;
        Shader::Terrain_Shader m_shader;
        Texture::Basic_Texture m_texture;
    };
}

#endif // TERRAIN_RENDERER_H_INCLUDED
