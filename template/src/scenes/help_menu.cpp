#include "help_menu.hpp"
#include "ecs/entities/button.hpp"

HelpMenu::HelpMenu()= default;

HelpMenu::~HelpMenu() = default;

bool HelpMenu::init() {
    Scene::init();
    return true;
}
