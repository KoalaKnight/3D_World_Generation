#include "FBO.h"

#include <iostream>
#include <stdexcept>

#include "Display.h"

FBO::FBO(int width, int height, bool depthAsTexture)
:   m_depthAsTexture(depthAsTexture)
,   m_width(width)
,   m_height(height)
{
    createFrameBuffer();
    createTextureAttachment();
    if(depthAsTexture)
    {
        createDepthAttachment();
    }
    else
    {
        createDepthBufferAttachment();
    }
    unbind();
}

FBO::~FBO()
{
    glDeleteFramebuffers(1, &m_frameBuffer);
    glDeleteTextures(1, &m_texture);
    if(m_depthAsTexture)
    {
        glDeleteTextures(1, &m_depthTexture);
    }
    else
    {
        glDeleteRenderbuffers(1, &m_depthBuffer);
    }
}

void FBO::bind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    glViewport(0, 0, m_width, m_height);
    glClearColor(0.57, 0.77, 0.81, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void FBO::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Display::WIDTH, Display::HEIGHT);
}

GLuint FBO::getTexture()
{
    return m_texture;
}

GLuint FBO::getDepthTexture()
{
    if(m_depthAsTexture)
    {
        return m_depthTexture;
    }
    else
    {
        throw std::runtime_error ("Error FBO asked to get Depth Texture when Depth Render Buffer being used");
    }
}

void FBO::createFrameBuffer()
{
    glGenFramebuffers(1, &m_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
}

void FBO::createTextureAttachment()
{
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texture, 0);
}

void FBO::createDepthAttachment()
{
    glGenTextures(1, &m_depthTexture);
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depthTexture, 0);
}

void FBO::createDepthBufferAttachment()
{
    glGenRenderbuffers(1, &m_depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);
}
