#include <ecs/systems/default_physics_system.hpp>
#include "snow_mountain_level.hpp"

SnowMountainLevel::SnowMountainLevel() :
        Level() {
}

void SnowMountainLevel::init_walking_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Spider s(texture, pos);
    s.drawable->texture->height = 50;
    s.physics->walk_speed = 85;
    s.physics->velocity.x = s.physics->walk_speed;
    m_entities.emplace_back(s);
}

void SnowMountainLevel::init_throwing_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Glob g(texture, pos);
    g.shooting->time = 4000;
    g.drawable->texture->height = 320;
    g.drawable->texture->width = 250;
    m_entities.emplace_back(g);
}

bool SnowMountainLevel::init_player() {
    Player player;
    player.airdash = new AirDash();
    m_entities.emplace_back(player);
    m_player = &m_entities.back();
    return true;
}

bool SnowMountainLevel::init() {
    m_background_music = Mix_LoadMUS(audio_path("snow.wav"));
    m_airdash_system = new AirDashSystem();
    m_physics_system = new DefaultPhysicsSystem(true);

    m_intro_modal = new Modal(textures_path("modals/snow-mountain.png"));
    return Level::init();
}


