#include "level_select.hpp"

#include "ecs/entities/button.hpp"

LevelSelect::LevelSelect() {
}

bool LevelSelect::init() {
    m_background_music = Mix_LoadMUS(audio_path("mainmenu.wav"));
    
    Button forest(textures_path("level-select/button-forest.png"));
    forest.position = {187.5,500.f};
    forest.m_button_callback = [this](){load_scene(FOREST);};
    m_buttons.emplace_back(forest);

    Button cave(textures_path("level-select/button-cave.png"));
    if (!m_unlocked_levels->at(CAVE)) {
        cave.drawable->texture_path = textures_path("level-select/button-lock.png");
        cave.active = false;
    }
    cave.position = {462.5,500.f};
    cave.m_button_callback = [this](){load_scene(CAVE);};
    m_buttons.emplace_back(cave);

    Button snow(textures_path("level-select/button-snow-mountain.png"));
    if (!m_unlocked_levels->at(SNOW_MOUNTAIN)) {
        snow.drawable->texture_path = textures_path("level-select/button-lock.png");
        snow.active = false;
    }
    snow.position = {737.5,500.f};
    snow.m_button_callback = [this](){load_scene(SNOW_MOUNTAIN);};
    m_buttons.emplace_back(snow);

    Button boss(textures_path("level-select/button-night-sky.png"));
    if (!m_unlocked_levels->at(NIGHT_SKY)) {
        boss.drawable->texture_path = textures_path("level-select/button-lock.png");
        boss.active = false;
    }
    boss.position = {1012.5,500.f};
    boss.active = true;
    boss.m_button_callback = [this](){load_scene(NIGHT_SKY);};
    m_buttons.emplace_back(boss);

    Button home(textures_path("buttons/home.png"));
    home.m_button_callback = [this](){load_scene(MAIN_MENU);};
    home.scale = {0.5f, 0.5f};
    home.position = {1150.f, 50.f};
    m_buttons.emplace_back(home);

    Button help_btn(textures_path("buttons/help.png"));
    help_btn.m_button_callback = [this](){drawHelp = !drawHelp; state = (state == RUNNING) ? PAUSED : RUNNING;};
    help_btn.scale = {0.5f, 0.5f};
    help_btn.position = {1070.f, 50.f};
    m_buttons.emplace_back(help_btn);
    
    Scene::init();
    return true;
}

