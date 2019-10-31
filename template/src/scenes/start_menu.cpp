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
    m_entities.emplace_back(start);
    Button help(textures_path("help.png"));
    help.position = {600.f,600.f};
    m_entities.emplace_back(help);
    Scene::init();
    return true;
}

void StartMenu::update(float elapsed_ms) {

}

bool StartMenu::is_forward() {
    return false;
}

vec2 StartMenu::get_player_position(){
    return vec2{600.f, 400.f};
}