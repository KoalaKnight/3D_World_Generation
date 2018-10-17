#ifndef WATER_RENDERER_H_INCLUDED
#define WATER_RENDERER_H_INCLUDED

#include <vector>
#include "../World/Water.h"
#include "../Camera.h"
#include "../Shaders/Water_Shader.h"
#include "../Glm_Common.h"
#include "../Texture/Texture.h"

namespace Renderer
{
    class Water_Renderer
    {
    public:
        Water_Renderer();
        void draw(const World::Water& water);
        void update(const Camera& camera, Vector3 lightPos, GLuint reflectTexture, GLuint refractTexture, GLuint depthTexture, float time);
    private:
        std::vector<const World::Water*> m_waters;
        Shader::Water_Shader m_shader;
        Texture::Basic_Texture m_dudvTexture;
        Texture::Basic_Texture m_normalTexture;
        float m_moveFactor = 0.0f;
        const float m_WAVESPEED = 0.04f;
    };
}

#endif // WATER_RENDERER_H_INCLUDED
