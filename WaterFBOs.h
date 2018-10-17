#ifndef WATERFBOS_H_INCLUDED
#define WATERFBOS_H_INCLUDED

#include <GL/glew.h>

#include "FBO.h"

class WaterFBOs
{
public:
    WaterFBOs(int reflectW, int reflectH, int refractW, int refractH);

    void bindReflectionFBO();
    void bindRefractionFBO();
    void unbind();

    GLuint getReflectionTexture();
    GLuint getRefractionTexture();
    GLuint getRefractionDepthTexture();
private:
    FBO reflectionFBO;
    FBO refractionFBO;
};

#endif // WATERFBOS_H_INCLUDED
