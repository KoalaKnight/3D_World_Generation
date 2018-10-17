#include "Water_Renderer.h"

#include <math.h>

#include "../Maths/Matrix.h"

namespace Renderer
{
    Water_Renderer::Water_Renderer()
    {
        m_dudvTexture.load("waterDUDV");
        m_normalTexture.load("normalMap");
    }

    void Water_Renderer::draw(const World::Water& water)
    {
        m_waters.push_back(&water);
    }

    void Water_Renderer::update(const Camera& camera, Vector3 lightPos, GLuint reflectTexture, GLuint refractTexture, GLuint depthTexture, float time)
    {
        m_shader.bind();
        m_shader.connectTextureUnits();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, reflectTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, refractTexture);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, m_dudvTexture.getTextureID());
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, m_normalTexture.getTextureID());
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        m_shader.setViewMatrix(camera.getViewMatrix());
        m_shader.setProjMatrix(camera.getProjectionMatrix());
        m_shader.setLightPos(lightPos);
        m_shader.setViewPos(camera.position);
        m_shader.setMoveFactor(m_moveFactor);

        for(auto& water : m_waters)
        {
            m_moveFactor += m_WAVESPEED * time;
            m_moveFactor = fmod(m_moveFactor, 1.0);
            water->bind();
            m_shader.setModelMatrix(Maths::createModelMatrix(*water));

            glDrawElements(GL_TRIANGLES, water->getIndicesCount(), GL_UNSIGNED_INT, nullptr);

            water->unbind();
        }
        glDisable(GL_BLEND);
        m_shader.unbind();
        m_waters.clear();
    }
}
