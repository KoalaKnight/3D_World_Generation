#ifndef MODEL_SHADER_H_INCLUDED
#define MODEL_SHADER_H_INCLUDED

#include "Shader_Program.h"

namespace Shader
{
    class Model_Shader : public Shader_Program
    {
    public:
        Model_Shader();

        void setViewMatrix(const Matrix4& matrix);
        void setModelMatrix(const Matrix4& matrix);
        void setProjMatrix(const Matrix4& matrix);
        void setLightPos(const Vector3& vec);
        void setViewPos(const Vector3& vec);
        void setPlane(const Vector4& vec);
    private:
        virtual void getUniformLocations() override;

        GLuint m_locationViewMatrix = 0;
        GLuint m_locationModelMatrix = 0;
        GLuint m_locationProjMatrix = 0;
        GLuint m_locationLightPos = 0;
        GLuint m_locationViewPos = 0;
        GLuint m_locationPlane = 0;
    };
}

#endif // MODEL_SHADER_H_INCLUDED
