#include "Terrain_Renderer.h"

#include "../Maths/Matrix.h"

namespace Renderer
{
    Terrain_Renderer::Terrain_Renderer()
    {
        m_texture.load("Texture_Atlas");
    }

    void Terrain_Renderer::draw(const World::Terrain& terrain)
    {
        m_terrains.push_back(&terrain);
    }

    void Terrain_Renderer::update(const Camera& camera, Vector3 lightPos, Vector4 plane)
    {
        m_shader.bind();
        m_shader.connectTextureUnits();
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, m_texture.getTextureID());
        m_shader.setViewMatrix(camera.getViewMatrix());
        m_shader.setProjMatrix(camera.getProjectionMatrix());
        m_shader.setLightPos(lightPos);
        m_shader.setViewPos(camera.position);
        m_shader.setPlane(plane);

        for(auto& terrain : m_terrains)
        {
            terrain->bind();
            m_shader.setModelMatrix(Maths::createModelMatrix(*terrain));

            glDrawElements(GL_TRIANGLES, terrain->getIndicesCount(), GL_UNSIGNED_INT, nullptr);

            terrain->unbind();
        }
        m_shader.unbind();
        m_terrains.clear();
    }
}
