#include <ecs/systems/default_physics_system.hpp>
#include "cave_level.hpp"

CaveLevel::CaveLevel() :
    Level() {
}

void CaveLevel::init_walking_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Spider s(texture, pos);
    m_entities.emplace_back(s);
}

void CaveLevel::init_throwing_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Glob g(texture, pos);
    m_entities.emplace_back(g);
}

bool CaveLevel::init_player() {
    Player player;
    m_entities.emplace_back(player);
    m_player = &m_entities.back();
    return true;
}

bool CaveLevel::init() {
    m_background_music = Mix_LoadMUS(audio_path("cave.wav"));
    Mix_VolumeMusic(MIX_MAX_VOLUME/2);
    m_physics_system = new DefaultPhysicsSystem(true);
    m_intro_modal = new Modal(textures_path("modals/cave.png"));

    return Level::init();
}
