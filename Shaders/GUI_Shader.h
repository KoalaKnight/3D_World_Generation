#ifndef GUI_SHADER_H_INCLUDED
#define GUI_SHADER_H_INCLUDED

#include "Shader_Program.h"

namespace Shader
{
    class GUI_Shader : public Shader_Program
    {
    public:
        GUI_Shader();
        void connectTextureUnits(int value);
    private:
        virtual void getUniformLocations() override;
        GLuint m_locationTexture = 0;
    };
}

#endif // GUI_SHADER_H_INCLUDED
