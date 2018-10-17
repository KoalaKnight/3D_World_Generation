#include "Water_Shader.h"

namespace Shader
{
    Water_Shader::Water_Shader()
    :   Shader_Program("Water_Vertex", "Water_Fragment")
    {
        getUniformLocations();
    }

    void Water_Shader::setViewMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_locationViewMatrix, matrix);
    }

    void Water_Shader::setModelMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_locationModelMatrix, matrix);
    }

    void Water_Shader::setProjMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_locationProjMatrix, matrix);
    }

    void Water_Shader::setLightPos(const Vector3& vec)
    {
        loadVector3(m_locationLightPos, vec);
    }

    void Water_Shader::setViewPos(const Vector3& vec)
    {
        loadVector3(m_locationViewPos, vec);
    }

    void Water_Shader::setMoveFactor(const float& value)
    {
        loadFloat(m_locationMoveFactor, value);
    }

    void Water_Shader::connectTextureUnits()
    {
        loadInt(m_locationReflectionTexture, 0);
        loadInt(m_locationRefractionTexture, 1);
        loadInt(m_locationDuDvTexture, 3);
        loadInt(m_locationNormalTexture, 4);
        loadInt(m_locationDepthTexture, 5);
    }

    void Water_Shader::getUniformLocations()
    {
        m_locationViewMatrix = glGetUniformLocation(getID(), "viewMatrix");
        m_locationModelMatrix = glGetUniformLocation(getID(), "modelMatrix");
        m_locationProjMatrix = glGetUniformLocation(getID(), "projMatrix");
        m_locationLightPos = glGetUniformLocation(getID(), "lightPos");
        m_locationViewPos = glGetUniformLocation(getID(), "viewPos");
        m_locationReflectionTexture = glGetUniformLocation(getID(), "reflectionTexture");
        m_locationRefractionTexture = glGetUniformLocation(getID(), "refractionTexture");
        m_locationDuDvTexture = glGetUniformLocation(getID(), "dudvMap");
        m_locationMoveFactor = glGetUniformLocation(getID(), "moveFactor");
        m_locationNormalTexture = glGetUniformLocation(getID(), "normalMap");
        m_locationDepthTexture = glGetUniformLocation(getID(), "depthMap");
    }
}
