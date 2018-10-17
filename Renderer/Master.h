#ifndef MASTER_H_INCLUDED
#define MASTER_H_INCLUDED

#include "Terrain_Renderer.h"
#include "Light_Renderer.h"
#include "Water_Renderer.h"
#include "GUI_Renderer.h"
#include "Model_Renderer.h"
#include "Multiple_Models_Renderer.h"
#include "../Glm_Common.h"

class Camera;
namespace World
{
    class Terrain;
    class Light;
    class Water;
}
namespace GUI
{
    class GUI;
}

namespace Renderer
{
    class Master
    {
        public:
            void clear();

            void update(const Camera& camera, Vector3 lightPos, Vector4 plane, GLuint reflectTexture, GLuint refractTexture, GLuint depthTexture, float time);
            void updateDisplay();

            void draw(const World::Terrain& model);
            void draw(const World::Light& model);
            void draw(const World::Water& model);
            void draw(const GUI::GUI& model, GLuint texture);
            void draw(const Model& model);
            void draw(Multiple_Models& model);
        private:
            Terrain_Renderer m_terrainRenderer;
            Light_Renderer m_lightRenderer;
            Water_Renderer m_waterRenderer;
            GUI_Renderer m_GUIRenderer;
            Model_Renderer m_modelRenderer;
            Multiple_Models_Renderer m_multipleModelsRenderer;
    };
}

#endif // MASTER_H_INCLUDED
