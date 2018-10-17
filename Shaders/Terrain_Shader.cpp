#include "Terrain_Shader.h"

namespace Shader
{
    Terrain_Shader::Terrain_Shader()
    :   Shader_Program("Terrain_Vertex", "Terrain_Fragment")
    {
        getUniformLocations();
    }

    void Terrain_Shader::setViewMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_locationViewMatrix, matrix);
    }

    void Terrain_Shader::setModelMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_locationModelMatrix, matrix);
    }

    void Terrain_Shader::setProjMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_locationProjMatrix, matrix);
    }

    void Terrain_Shader::setLightPos(const Vector3& vec)
    {
        loadVector3(m_locationLightPos, vec);
    }

    void Terrain_Shader::setViewPos(const Vector3& vec)
    {
        loadVector3(m_locationViewPos, vec);
    }

    void Terrain_Shader::setPlane(const Vector4& vec)
    {
        loadVector4(m_locationPlane, vec);
    }

    void Terrain_Shader::connectTextureUnits()
    {
        loadInt(m_locationTexture, 2);
    }

    void Terrain_Shader::getUniformLocations()
    {
        m_locationViewMatrix = glGetUniformLocation(getID(), "viewMatrix");
        m_locationModelMatrix = glGetUniformLocation(getID(), "modelMatrix");
        m_locationProjMatrix = glGetUniformLocation(getID(), "projMatrix");
        m_locationLightPos = glGetUniformLocation(getID(), "lightPos");
        m_locationViewPos = glGetUniformLocation(getID(), "viewPos");
        m_locationPlane = glGetUniformLocation(getID(), "plane");
        m_locationTexture = glGetUniformLocation(getID(), "ourTexture");
    }
}
