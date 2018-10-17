#include "Application.h"

#include <SFML/System/Clock.hpp>
#include <vector>
#include <iostream>

#include "Display.h"
#include "World/Terrain.h"
#include "World/Water.h"
#include "Util/Random.h"
#include "GUI/GUI.h"
#include "WaterFBOs.h"
#include "Maths/Matrix.h"
#include "Models/Model.h"
#include "Models/Multiple_Models.h"

Application::Application()
:   m_light({0.0f, -1.0f, 5.0f})
//,   m_textureAtlas("Texture_Atlas", 1024, 512)
{
    //m_textureAtlas.bind();
}

void Application::runMainGameLoop()
{
    sf::Clock clock;
    World::Terrain terrain = World::Terrain(300, 300, 0.05f, {0.0f, -2.0f, 0.0f});
    World::Water water = World::Water(15.0f, {0.0f, -1.95f, 0.0f});
    //GUI::GUI gui = GUI::GUI(0.6f, {-1.0f, 0.4f});
    //GUI::GUI gui2 = GUI::GUI(0.6f, {0.4f, 0.4f});
    WaterFBOs fbos = WaterFBOs(Display::WIDTH, Display::HEIGHT, Display::WIDTH, Display::HEIGHT);
    //World::Light box = World::Light({2.0f, -3.9f, 2.0f});
    float waterHeight = (Maths::createModelMatrix(water) * Vector4(water.position.x, water.position.y, water.position.z, 1.0)).y;
    Camera waterCamera;
    //Model model = Model("tree", {2.0, -4.0, 2.0}, 0.1);
    Multiple_Models multiModels = Multiple_Models("tree", terrain.m_treePositions, 0.03);

    while (Display::isOpen())
    {
        auto dt = clock.restart().asSeconds();
        m_renderer.clear();

        //Player input not affecting camera

        m_camera.update();
        m_camera.input(dt);

        waterCamera.position = m_camera.position;
        waterCamera.rotation = m_camera.rotation;
        waterCamera.position.y = waterCamera.position.y - (2 * (m_camera.position.y - waterHeight));
        waterCamera.rotation.x *= -1;

        waterCamera.update();

        fbos.bindReflectionFBO();
        //Draw objects
        m_renderer.draw(terrain);
        //m_renderer.draw(box);
        //m_renderer.draw(model);
        m_renderer.draw(multiModels);
        m_renderer.update(waterCamera, m_light.position, {0.0, 1.0, 0.0, -waterHeight}, fbos.getReflectionTexture(), fbos.getRefractionTexture(), fbos.getRefractionDepthTexture(), dt);
        fbos.unbind();

        fbos.bindRefractionFBO();
        m_renderer.draw(terrain);
        //m_renderer.draw(box);
        //m_renderer.draw(model);
        m_renderer.draw(multiModels);
        m_renderer.update(m_camera, m_light.position, {0.0, -1.0, 0.0, waterHeight}, fbos.getReflectionTexture(), fbos.getRefractionTexture(), fbos.getRefractionDepthTexture(), dt);
        fbos.unbind();

        m_renderer.draw(terrain);
        //m_renderer.draw(box);
        m_renderer.draw(m_light);
        m_renderer.draw(water);
        //m_renderer.draw(model);
        m_renderer.draw(multiModels);
        //m_renderer.draw(gui, fbos.getReflectionTexture());
        //m_renderer.draw(gui2, fbos.getRefractionTexture());

        m_renderer.update(m_camera, m_light.position, {0.0, 0.0, 0.0, 0}, fbos.getReflectionTexture(), fbos.getRefractionTexture(), fbos.getRefractionDepthTexture(), dt);
        m_renderer.updateDisplay();

        Display::checkForClose();
    }
}
