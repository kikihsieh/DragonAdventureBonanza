//
// Created by arden on 10/15/2019.
//

#include <functional>
#include "start_menu.hpp"
#include "ecs/entities/button.hpp"

StartMenu::StartMenu()  {
}

bool StartMenu::init() {
    Button start(textures_path("start.png"));
    start.position = {600.f,400.f};
    start.m_button_callback = [this](){load_scene(FOREST);};
    m_buttons.emplace_back(start);
    m_entities.emplace_back(start);
    Button help(textures_path("help.png"));
    help.position = {600.f,600.f};
    help.m_button_callback = [this]() {drawHelp = !drawHelp;};
    m_entities.emplace_back(help);
    m_buttons.emplace_back(help);
    Button exit(textures_path("exit.png"));
    exit.position = {50.f,750.f};
    exit.scale = {0.35f, 0.35f};
    exit.m_button_callback = [this](){exit_game();};
    m_entities.emplace_back(exit);
    m_buttons.emplace_back(exit);
    m_background_music = Mix_LoadWAV(audio_path("mainmenu.wav"));
    Scene::init();
    
    return true;
}
