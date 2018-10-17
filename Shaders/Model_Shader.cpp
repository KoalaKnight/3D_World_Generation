#include "Model_Shader.h"

namespace Shader
{
    Model_Shader::Model_Shader()
    :   Shader_Program("Model_Vertex", "Model_Fragment")
    {
        getUniformLocations();
    }

    void Model_Shader::setViewMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_locationViewMatrix, matrix);
    }

    void Model_Shader::setModelMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_locationModelMatrix, matrix);
    }

    void Model_Shader::setProjMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_locationProjMatrix, matrix);
    }

    void Model_Shader::setLightPos(const Vector3& vec)
    {
        loadVector3(m_locationLightPos, vec);
    }

    void Model_Shader::setViewPos(const Vector3& vec)
    {
        loadVector3(m_locationViewPos, vec);
    }

    void Model_Shader::setPlane(const Vector4& vec)
    {
        loadVector4(m_locationPlane, vec);
    }

    void Model_Shader::getUniformLocations()
    {
        m_locationViewMatrix = glGetUniformLocation(getID(), "viewMatrix");
        m_locationModelMatrix = glGetUniformLocation(getID(), "modelMatrix");
        m_locationProjMatrix = glGetUniformLocation(getID(), "projMatrix");
        m_locationLightPos = glGetUniformLocation(getID(), "lightPos");
        m_locationViewPos = glGetUniformLocation(getID(), "viewPos");
        m_locationPlane = glGetUniformLocation(getID(), "plane");
    }
}
