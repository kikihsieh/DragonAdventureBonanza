#ifndef DAB_FINAL_BOSS_SYSTEM_HPP
#define DAB_FINAL_BOSS_SYSTEM_HPP

#include <ecs/entities/entity.hpp>
#include <list>
#include "final_boss_spawning_system.hpp"

class FinalBossSystem {
public:

    bool init(Entity& final_boss, std::list<Entity> *entities, vec2 screen_bounds, FinalBossSpawningSystem* final_boss_spawning_system);

    void update(Entity& final_boss, float ms);

private:

    void phase_1 (Entity& final_boss, float ms);
    void phase_2 (Entity& final_boss, float ms);
    void phase_3 (Entity& final_boss, float ms);

    float m_phase_1_timer;
    float m_phase_1_frequency;
    int m_final_boss_max_health;

    vec2 m_screen_bounds;

    std::list<Entity>* m_entities;


    FinalBossSpawningSystem* m_final_boss_spawning_system;
};

#endif //DAB_FINAL_BOSS_SYSTEM_HPP
