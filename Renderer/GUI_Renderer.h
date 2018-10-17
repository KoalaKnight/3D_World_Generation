#ifndef GUI_RENDERER_H_INCLUDED
#define GUI_RENDERER_H_INCLUDED

#include <vector>
#include "../GUI/GUI.h"
#include "../Shaders/GUI_Shader.h"

namespace Renderer
{
    class GUI_Renderer
    {
    public:
        void draw(const GUI::GUI& gui, GLuint texture);
        void update();
    private:
        std::vector<const GUI::GUI*> m_GUIs;
        std::vector<GLuint> m_textures;
        Shader::GUI_Shader m_shader;
    };
}

#endif // GUI_RENDERER_H_INCLUDED
