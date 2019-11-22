#include "level_select.hpp"

#include "ecs/entities/button.hpp"

LevelSelect::LevelSelect()  {
}

bool LevelSelect::init() {
    Button forest(textures_path("level-select/button-forest.png"));
    forest.position = {187.5,400.f};
    forest.m_button_callback = [this](){load_scene(FOREST);};
    m_buttons.emplace_back(forest);
    m_entities.emplace_back(forest);
    Button cave(textures_path("level-select/button-cave.png"));
    if (m_unlocked_levels->at(CAVE) == false) {
        cave.drawable->texture_path = textures_path("level-select/button-lock.png");
        cave.active = false;
    }
    cave.position = {462.5,400.f};
    cave.m_button_callback = [this](){load_scene(CAVE);};
    m_buttons.emplace_back(cave);
    m_entities.emplace_back(cave);
    Button snow(textures_path("level-select/button-snow-mountain.png"));
    if (m_unlocked_levels->at(SNOW_MOUNTAIN) == false) {
        snow.drawable->texture_path = textures_path("level-select/button-lock.png");
        snow.active = false;
    }
    snow.position = {737.5,400.f};
    snow.m_button_callback = [this](){load_scene(SNOW_MOUNTAIN);};
    m_buttons.emplace_back(snow);
    m_entities.emplace_back(snow);
    Button boss(textures_path("level-select/button-night-sky.png"));
    if (true) {
        boss.drawable->texture_path = textures_path("level-select/button-lock.png");
        boss.active = false;
    }
    boss.position = {1012.5,400.f};
    boss.active = false;
//    boss.m_button_callback = [this](){load_scene();};
    m_buttons.emplace_back(boss);
    m_entities.emplace_back(boss);
    Scene::init();
    return true;
}

