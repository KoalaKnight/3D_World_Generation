#include "Light_Shader.h"

namespace Shader
{
    Light_Shader::Light_Shader()
    :   Shader_Program("Light_Vertex", "Light_Fragment")
    {
        getUniformLocations();
    }

    void Light_Shader::setViewMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_locationViewMatrix, matrix);
    }

    void Light_Shader::setModelMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_locationModelMatrix, matrix);
    }

    void Light_Shader::setProjMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_locationProjMatrix, matrix);
    }

    void Light_Shader::setPlane(const Vector4& vec)
    {
        loadVector4(m_locationPlane, vec);
    }

    void Light_Shader::getUniformLocations()
    {
        m_locationViewMatrix = glGetUniformLocation(getID(), "viewMatrix");
        m_locationModelMatrix = glGetUniformLocation(getID(), "modelMatrix");
        m_locationProjMatrix = glGetUniformLocation(getID(), "projMatrix");
        m_locationPlane = glGetUniformLocation(getID(), "plane");
    }
}
