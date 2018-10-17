#ifndef FBO_H_INCLUDED
#define FBO_H_INCLUDED

#include <GL/glew.h>

class FBO
{
public:
    FBO(int width, int height, bool depthAsTexture);
    ~FBO();

    void bind();
    void unbind();

    GLuint getTexture();
    GLuint getDepthTexture();
private:
    void createFrameBuffer();
    void createTextureAttachment();
    void createDepthAttachment();
    void createDepthBufferAttachment();

    bool m_depthAsTexture = false;
    int m_width = 0;
    int m_height = 0;
    GLuint m_frameBuffer = 0;
    GLuint m_texture = 0;
    GLuint m_depthBuffer = 0;
    GLuint m_depthTexture = 0;
};

#endif // FBO_H_INCLUDED
