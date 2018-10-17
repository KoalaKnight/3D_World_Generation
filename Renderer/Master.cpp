#include "Master.h"

#include "../Display.h"

namespace Renderer
{
    void Master::clear()
    {
        Display::clear();
    }

    void Master::update(const Camera& camera, Vector3 lightPos, Vector4 plane, GLuint reflectTexture, GLuint refractTexture, GLuint depthTexture, float time)
    {
        m_terrainRenderer.update(camera, lightPos, plane);
        m_waterRenderer.update(camera, lightPos, reflectTexture, refractTexture, depthTexture, time);
        m_lightRenderer.update(camera, plane);
        m_GUIRenderer.update();
        m_modelRenderer.update(camera, lightPos, plane);
        m_multipleModelsRenderer.update(camera, lightPos, plane);
    }

    void Master::updateDisplay()
    {
        Display::update();
    }

    void Master::draw(const World::Terrain& model)
    {
        m_terrainRenderer.draw(model);
    }

    void Master::draw(const World::Light& model)
    {
        m_lightRenderer.draw(model);
    }

    void Master::draw(const World::Water& model)
    {
        m_waterRenderer.draw(model);
    }

    void Master::draw(const GUI::GUI& model, GLuint texture)
    {
        m_GUIRenderer.draw(model, texture);
    }

    void Master::draw(const Model& model)
    {
        m_modelRenderer.draw(model);
    }

    void Master::draw(Multiple_Models& model)
    {
        m_multipleModelsRenderer.draw(model);
    }
}
