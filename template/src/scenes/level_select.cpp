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
    cave.position = {462.5,400.f};
    cave.m_button_callback = [this](){load_scene(CAVE);};
    m_buttons.emplace_back(cave);
    m_entities.emplace_back(cave);
    Button snow(textures_path("level-select/button-snow-mountain.png"));
    snow.position = {737.5,400.f};
    snow.m_button_callback = [this](){load_scene(SNOW_MOUNTAIN);};
    m_buttons.emplace_back(snow);
    m_entities.emplace_back(snow);
    Button boss(textures_path("level-select/button-lock.png"));
    boss.position = {1012.5,400.f};
    boss.active = false;
//    boss.m_button_callback = [this](){load_scene();};
    m_buttons.emplace_back(boss);
    m_entities.emplace_back(boss);
    Scene::init();
    return true;
}

