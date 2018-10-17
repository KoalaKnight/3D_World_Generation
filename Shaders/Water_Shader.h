#ifndef WATER_SHADER_H_INCLUDED
#define WATER_SHADER_H_INCLUDED

#include "Shader_Program.h"

namespace Shader
{
    class Water_Shader : public Shader_Program
    {
    public:
        Water_Shader();

        void setViewMatrix(const Matrix4& matrix);
        void setModelMatrix(const Matrix4& matrix);
        void setProjMatrix(const Matrix4& matrix);
        void setLightPos(const Vector3& vec);
        void setViewPos(const Vector3& vec);
        void setMoveFactor(const float& value);
        void connectTextureUnits();
    private:
        virtual void getUniformLocations() override;

        GLuint m_locationViewMatrix = 0;
        GLuint m_locationModelMatrix = 0;
        GLuint m_locationProjMatrix = 0;
        GLuint m_locationLightPos = 0;
        GLuint m_locationViewPos = 0;
        GLuint m_locationReflectionTexture = 0;
        GLuint m_locationRefractionTexture = 0;
        GLuint m_locationDuDvTexture = 0;
        GLuint m_locationMoveFactor = 0;
        GLuint m_locationNormalTexture = 0;
        GLuint m_locationDepthTexture = 0;
    };
}

#endif // WATER_SHADER_H_INCLUDED
