#ifndef LIGHT_SHADER_H_INCLUDED
#define LIGHT_SHADER_H_INCLUDED

#include "Shader_Program.h"

namespace Shader
{
    class Light_Shader : public Shader_Program
    {
    public:
        Light_Shader();

        void setViewMatrix(const Matrix4& matrix);
        void setModelMatrix(const Matrix4& matrix);
        void setProjMatrix(const Matrix4& matrix);
        void setPlane(const Vector4& vec);
    private:
        virtual void getUniformLocations() override;

        GLuint m_locationViewMatrix = 0;
        GLuint m_locationModelMatrix = 0;
        GLuint m_locationProjMatrix = 0;
        GLuint m_locationPlane = 0;
    };
}

#endif // LIGHT_SHADER_H_INCLUDED
