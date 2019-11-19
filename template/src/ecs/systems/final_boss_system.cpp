#include <ecs/systems/final_boss_system.hpp>
#include <sstream>
#include <vector>

bool FinalBossSystem::init(Entity& final_boss, std::list<Entity> *entities, vec2 screen_size, FinalBossSpawningSystem* final_boss_spawning_system) {
    m_entities = entities;

    m_phase_1_timer = 3000;
    m_phase_1_frequency = 3000;

    final_boss.physics->velocity.y = -100;
    m_final_boss_max_health = final_boss.health->health;

    m_screen_bounds = screen_size;

    m_final_boss_spawning_system = final_boss_spawning_system;
    return true;
}

void FinalBossSystem::update(Entity& final_boss, float ms) {

    if (final_boss.health->health > m_final_boss_max_health * 2/3)
        phase_1(final_boss, ms);
    else if (final_boss.health->health > m_final_boss_max_health * 1/3)
        phase_2(final_boss, ms);
    else
        phase_3(final_boss, ms);
}

void FinalBossSystem::phase_1(Entity& final_boss, float ms) {

    float height = final_boss.texture_size.y * final_boss.scale.y + 50;

    if (final_boss.position.y - height / 2 <= 0 || final_boss.position.y + height / 2 >= m_screen_bounds.y) {
        final_boss.physics->velocity.y = -1 * final_boss.physics->velocity.y;
    }

    m_phase_1_timer += ms;

    if (m_phase_1_timer >= m_phase_1_frequency) {
        m_phase_1_timer = 0;

        float width = final_boss.texture_size.x * final_boss.scale.x + 50;
        m_final_boss_spawning_system->spawn_bomb(sub(final_boss.position, {width / 2, 0}));
    }
}


void FinalBossSystem::phase_2(Entity& final_boss, float ms) {

    std::cout << "Phase 2" << std::endl;
    float height = final_boss.texture_size.y * final_boss.scale.y + 50;

    if (final_boss.position.y - height / 2 <= 0 || final_boss.position.y + height / 2 >= m_screen_bounds.y) {
        final_boss.physics->velocity.y = -1 * final_boss.physics->velocity.y;
    }
}


void FinalBossSystem::phase_3(Entity& final_boss, float ms) {

    std::cout << "Phase 3" << std::endl;
    float height = final_boss.texture_size.y * final_boss.scale.y + 50;

    if (final_boss.position.y - height / 2 <= 0 || final_boss.position.y + height / 2 >= m_screen_bounds.y) {
        final_boss.physics->velocity.y = -1 * final_boss.physics->velocity.y;
    }
}
