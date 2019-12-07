#include <ecs/entities/spider.hpp>
#include <ecs/systems/default_physics_system.hpp>
#include "forest_level.hpp"

ForestLevel::ForestLevel() :
    Level() {
}

void ForestLevel::init_walking_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Spider s(texture, pos);
    m_entities.emplace_back(s);
}

void ForestLevel::init_throwing_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Glob g(texture, pos);
    g.scale.y *= 1.25;
    m_entities.emplace_back(g);
}

bool ForestLevel::init_player() {
    Player player;
    m_entities.emplace_back(player);
    m_player = &m_entities.back();
    return true;
}

bool ForestLevel::init() {
    m_background_music = Mix_LoadMUS(audio_path("forest.wav"));
    Mix_VolumeMusic(MIX_MAX_VOLUME/5);
    m_physics_system = new DefaultPhysicsSystem(false);
    m_intro_modal = new Modal(textures_path("modals/forest.png"));

   return Level::init();
}


