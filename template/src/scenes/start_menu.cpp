//
// Created by arden on 10/15/2019.
//

#include "start_menu.hpp"

StartMenu::StartMenu()  {
}

StartMenu::~StartMenu() = default;

bool StartMenu::init() {
    Scene::init();
    std::shared_ptr<Button> start = std::make_shared<Button>();
    if(start->init({600, 400}, textures_path("start.png")))
        m_buttons.emplace_back(start);
    return true;
}

void StartMenu::destroy() {
    Scene::destroy();
    m_buttons.clear();
}

void StartMenu::update(float elapsed_ms) {
    for (auto& button : m_buttons) {
        button->update(elapsed_ms);
    }
}

void StartMenu::draw(const mat3 &projection) {
    Scene::draw(projection);
    for (auto &button : m_buttons) {
        button.get()->draw(projection);
    }
}