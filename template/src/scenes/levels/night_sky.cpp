#include <ecs/entities/cloud.hpp>
#include <sstream>
#include <ecs/systems/flying_physics_system.hpp>
#include <ecs/entities/final_boss.hpp>
#include "night_sky.hpp"

NightSky::NightSky() :
    Level() {
}

bool NightSky::init() {
    m_background_music = Mix_LoadMUS(audio_path("nightsky.wav"));
    m_screen = {1200, 800};

    m_intro_modal = new Modal(textures_path("modals/night-sky.png"));

    if(!m_final_boss_spawning_system.init(&m_entities, m_screen))
        return false;

    //=================================
    // Change to Flying Physics System
    //=================================
    m_physics_system = new FlyingPhysicsSystem();
    m_physics_system->init(&m_entities, m_screen);
    auto *flying_physics = dynamic_cast<FlyingPhysicsSystem *>(m_physics_system);
    flying_physics->set_spawning_system(&m_final_boss_spawning_system);

    bool init = Level::init();

    //=================================
    // Cloud Spawning
    //=================================
    m_spawn_cloud_frequency = 5500;
    m_spawn_cloud_timer = m_spawn_cloud_frequency;

    for (float x = 100; x <= m_screen.x; x += 150) {
        m_final_boss_spawning_system.spawn_cloud(x);
    }
  
    // Spawn Final Boss
    //=================================
    if(!m_final_boss_spawning_system.spawn_final_boss())
        return false;
    m_final_boss = &m_entities.back();

    return init && m_final_boss_system.init(m_player, *m_final_boss, &m_entities, m_screen, &m_final_boss_spawning_system, m_scene_change_callback);
}


void NightSky::update(float elapsed_ms, vec2 screen_size) {
    m_player->input->space = true;

    m_final_boss_system.update(*m_final_boss, elapsed_ms);
    Level::update(elapsed_ms, screen_size);

    m_spawn_cloud_timer += elapsed_ms;
    if (m_spawn_cloud_timer >= m_spawn_cloud_frequency) {
        spawn_cloud();
        m_spawn_cloud_timer = 0;
    }
}


void NightSky::spawn_cloud() {
    m_final_boss_spawning_system.spawn_cloud(0);
}

bool NightSky::init_player() {
    Player player;
    m_entities.emplace_back(player);
    m_player = &m_entities.back();
    m_player->physics->gravity = 0;
    m_player->physics->velocity = {0, 0};
    m_player->physics->acceleration = {0, 0};
    m_player->position = {100, 400};
    m_player->shooting->time = 500;
    return true;
}