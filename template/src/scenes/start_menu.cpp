#include "start_menu.hpp"
#include "ecs/entities/button.hpp"

StartMenu::StartMenu() {
}

bool StartMenu::init() {
    Button start(textures_path("main-menu/start.png"));
    start.position = {600.f,450.f};
    start.scale = {0.5f, 0.5f};
    start.m_button_callback = [this](){load_scene(STORYLINE);};
    m_buttons.emplace_back(start);

    Button level_select(textures_path("main-menu/levels.png"));
    level_select.position = {600.f,550.f};
    level_select.scale = {0.5f, 0.5f};
    level_select.m_button_callback = [this](){load_scene(LEVEL_SELECT);};
    m_buttons.emplace_back(level_select);

    Button help(textures_path("buttons/help.png"));
    help.position = {1150.f,50.f};
    help.scale = {0.5f, 0.5f};
    help.m_button_callback = [this]() {drawHelp = !drawHelp;};
    m_buttons.emplace_back(help);

    Button exit(textures_path("main-menu/exit.png"));
    exit.position = {600.f,650.f};
    exit.scale = {0.5f, 0.5f};
    exit.m_button_callback = [this](){exit_game();};
    m_buttons.emplace_back(exit);

    Button credit(textures_path("buttons/credits.png"));
    credit.position = {50.f,750.f};
    credit.scale = {0.5f, 0.5f};
    credit.m_button_callback = [this](){drawCredits = !drawCredits;};
    m_buttons.emplace_back(credit);
    
    m_background_music = Mix_LoadMUS(audio_path("mainmenu.wav"));
    Scene::init();
    
    return true;
}
