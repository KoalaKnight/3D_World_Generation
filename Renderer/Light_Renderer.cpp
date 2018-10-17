#include "Light_Renderer.h"

#include "../Maths/Matrix.h"

namespace Renderer
{
    void Light_Renderer::draw(const World::Light& light)
    {
        m_lights.push_back(&light);
    }

    void Light_Renderer::update(const Camera& camera, Vector4 plane)
    {
        m_shader.bind();
        m_shader.setViewMatrix(camera.getViewMatrix());
        m_shader.setProjMatrix(camera.getProjectionMatrix());
        m_shader.setPlane(plane);

        for(auto& light : m_lights)
        {
            light->bind();
            m_shader.setModelMatrix(Maths::createModelMatrix(*light));

            glDrawElements(GL_TRIANGLES, light->getIndicesCount(), GL_UNSIGNED_INT, nullptr);

            light->unbind();
        }
        m_shader.unbind();
        m_lights.clear();
    }
}
