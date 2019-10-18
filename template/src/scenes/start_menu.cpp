//
// Created by arden on 10/15/2019.
//

#include "start_menu.hpp"
#include "ecs/entities/button.hpp"

StartMenu::StartMenu()  {
}

StartMenu::~StartMenu() = default;

bool StartMenu::init() {
    Button start;
    m_entities.emplace_back(start);
    Scene::init();
    return true;
}

void StartMenu::destroy() {
    Scene::destroy();
    m_entities.clear();
}

void StartMenu::update(float elapsed_ms) {

}