#include <ecs/systems/final_boss_system.hpp>

bool FinalBossSystem::init(Entity final_boss, std::list<Entity> *entities) {
    m_final_boss = final_boss;
    m_entities = entities;

    m_phase_1_timer = 0;
    m_phase_1_frequency = 1000;

    return true;
}

void FinalBossSystem::update(float ms) {

    if (m_final_boss.health->health > m_final_boss.health->health * 2/3)
        phase_1(ms);
}

void FinalBossSystem::phase_1(float ms) {

    m_phase_1_timer += ms;

    if (m_phase_1_timer >= m_phase_1_frequency) {
        m_phase_1_timer = 0;


    }
}