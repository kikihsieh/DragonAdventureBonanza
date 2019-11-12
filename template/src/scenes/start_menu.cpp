//
// Created by arden on 10/15/2019.
//

#include "start_menu.hpp"
#include "ecs/entities/button.hpp"

StartMenu::StartMenu()  {
}

bool StartMenu::init() {
    Button start(textures_path("start.png"));
    start.position = {600.f,400.f};
    start.function = "level";
    start.scene_index = 0;
    m_buttons.emplace_back(start);
    m_entities.emplace_back(start);
    Button help(textures_path("help.png"));
    help.position = {600.f,600.f};
    help.function = "help";
    m_entities.emplace_back(help);
    m_buttons.emplace_back(help);
    Button exit(textures_path("exit.png"));
    exit.position = {50.f,750.f};
    exit.scale = {0.35f, 0.35f};
    exit.function = "close";
    m_entities.emplace_back(exit);
    m_buttons.emplace_back(exit);
    Scene::init();
    return true;
}
