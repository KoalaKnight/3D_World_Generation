#include "Model_Renderer.h"

#include "../Maths/Matrix.h"

namespace Renderer
{
    void Model_Renderer::draw(const Model& model)
    {
        m_models.push_back(&model);
    }

    void Model_Renderer::update(const Camera& camera, Vector3 lightPos, Vector4 plane)
    {
        m_shader.bind();
        m_shader.setViewMatrix(camera.getViewMatrix());
        m_shader.setProjMatrix(camera.getProjectionMatrix());
        m_shader.setLightPos(lightPos);
        m_shader.setViewPos(camera.position);
        m_shader.setPlane(plane);

        for(auto& model : m_models)
        {
            model->bind();
            m_shader.setModelMatrix(Maths::createModelMatrix(*model));

            glDrawElements(GL_TRIANGLES, model->getIndicesCount(), GL_UNSIGNED_INT, nullptr);

            model->unbind();
        }
        m_shader.unbind();
        m_models.clear();
    }
}
