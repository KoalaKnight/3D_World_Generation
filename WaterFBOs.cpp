#include "WaterFBOs.h"

WaterFBOs::WaterFBOs(int reflectW, int reflectH, int refractW, int refractH)
:   reflectionFBO(reflectW, reflectH, false)
,   refractionFBO(refractW, refractH, true)
{

}

void WaterFBOs::bindReflectionFBO()
{
    reflectionFBO.bind();
}

void WaterFBOs::bindRefractionFBO()
{
    refractionFBO.bind();
}

void WaterFBOs::unbind()
{
    reflectionFBO.unbind();
}

GLuint WaterFBOs::getReflectionTexture()
{
    return reflectionFBO.getTexture();
}

GLuint WaterFBOs::getRefractionTexture()
{
    return refractionFBO.getTexture();
}

GLuint WaterFBOs::getRefractionDepthTexture()
{
    return refractionFBO.getDepthTexture();
}
