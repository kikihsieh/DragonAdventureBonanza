#include "start_menu.hpp"
#include "ecs/entities/button.hpp"

StartMenu::StartMenu() {
}

bool StartMenu::init() {
    Button start(textures_path("start.png"));
    start.position = {600.f,400.f};
    start.m_button_callback = [this](){load_scene(STORYLINE);};
    m_buttons.emplace_back(start);

    Button level_select(textures_path("start.png"));
    level_select.position = {600.f,600.f};
    level_select.m_button_callback = [this](){load_scene(LEVEL_SELECT);};
    m_buttons.emplace_back(level_select);

    Button help(textures_path("buttons/help.png"));
    help.position = {1150.f,50.f};
    help.scale = {0.5f, 0.5f};
    help.m_button_callback = [this]() {drawHelp = !drawHelp;};
    m_buttons.emplace_back(help);

    Button exit(textures_path("exit.png"));
    exit.position = {50.f,750.f};
    exit.scale = {0.35f, 0.35f};
    exit.m_button_callback = [this](){exit_game();};
    m_buttons.emplace_back(exit);
    
    m_background_music = Mix_LoadMUS(audio_path("mainmenu.wav"));
    Scene::init();
    
    return true;
}
