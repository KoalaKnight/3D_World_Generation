#include "GUI_Shader.h"

namespace Shader
{
    GUI_Shader::GUI_Shader()
    :   Shader_Program("GUI_Vertex", "GUI_Fragment")
    {

    }

    void GUI_Shader::connectTextureUnits(int value)
    {
        loadInt(m_locationTexture, value);
    }

    void GUI_Shader::getUniformLocations()
    {
        m_locationTexture = glGetUniformLocation(getID(), "renderedTexture");
    }
}
