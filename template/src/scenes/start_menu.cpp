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
    Scene::init();
    
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "Failed to initialize SDL Audio");
        return false;
    }
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        fprintf(stderr, "Failed to open audio device");
        return false;
    }
    
    m_background_music = Mix_LoadWAV(audio_path("mainmenu.wav"));
    //m_salmon_dead_sound = Mix_LoadWAV(audio_path("salmon_dead.wav"));
    //m_salmon_eat_sound = Mix_LoadWAV(audio_path("salmon_eat.wav"));
    
    if (m_background_music == nullptr)
    {
        fprintf(stderr, "Failed to load sounds\n %s\n %s\n %s\n make sure the data directory is present",
                audio_path("mainmenu.wav"));
        return false;
    }
   
    // Playing background music indefinitely
    Mix_PlayChannel(-1,m_background_music, -1);
    
    fprintf(stderr, "Loaded music\n");
    
    return true;
}
