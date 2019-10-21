//
// Created by arden on 10/15/2019.
//

#include "help_menu.hpp"
#include "ecs/entities/button.hpp"

HelpMenu::HelpMenu(){
}

HelpMenu::~HelpMenu() = default;

bool HelpMenu::init() {
    Scene::init();
    return true;
}

void HelpMenu::destroy() {
    Scene::destroy();
    m_entities.clear();
}

void HelpMenu::update(float elapsed_ms) {

}

bool HelpMenu::is_forward() {
    return false;
}

vec2 HelpMenu::get_player_position(){
    return vec2{600.f, 400.f};
}