#include "Multiple_Models_Renderer.h"

#include "../Maths/Matrix.h"

namespace Renderer
{
    void Multiple_Models_Renderer::draw(Multiple_Models& multipleModels)
    {
        m_multipleModels.push_back(&multipleModels);
    }

    void Multiple_Models_Renderer::update(const Camera& camera, Vector3 lightPos, Vector4 plane)
    {
        for(auto& multipleModels : m_multipleModels)
        {
            m_shader.bind();
            m_shader.setViewMatrix(camera.getViewMatrix());
            m_shader.setProjMatrix(camera.getProjectionMatrix());
            m_shader.setLightPos(lightPos);
            m_shader.setViewPos(camera.position);
            m_shader.setPlane(plane);
            for(int i = 0; i < multipleModels->m_positions.size(); i++)
            {
                multipleModels->model.setPosition(multipleModels->m_positions[i]);
                multipleModels->model.bind();
                m_shader.setModelMatrix(Maths::createModelMatrix(multipleModels->model));

                glDrawElements(GL_TRIANGLES, multipleModels->model.getIndicesCount(), GL_UNSIGNED_INT, nullptr);

                multipleModels->model.unbind();
            }
        }
        m_shader.unbind();
        m_multipleModels.clear();
    }
}
