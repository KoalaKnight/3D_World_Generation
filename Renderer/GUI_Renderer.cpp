#include "GUI_Renderer.h"

#include <iostream>

namespace Renderer
{
    void GUI_Renderer::draw(const GUI::GUI& gui, GLuint texture)
    {
        m_GUIs.push_back(&gui);
        m_textures.push_back(texture);
    }

    void GUI_Renderer::update()
    {
        m_shader.bind();
        int i = 0;
        for(auto& gui : m_GUIs)
        {
            m_shader.connectTextureUnits(i);
            //glBindTexture(GL_TEXTURE_2D, m_textures[i]);
            gui->bind();

            glDrawElements(GL_TRIANGLES, gui->getIndicesCount(), GL_UNSIGNED_INT, nullptr);

            gui->unbind();
            i++;
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        m_shader.unbind();
        m_textures.clear();
        m_GUIs.clear();
    }
}
