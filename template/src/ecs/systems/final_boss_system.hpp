#ifndef DAB_FINAL_BOSS_SYSTEM_HPP
#define DAB_FINAL_BOSS_SYSTEM_HPP

#include <ecs/entities/entity.hpp>
#include <list>
#include "final_boss_spawning_system.hpp"

class FinalBossSystem {
public:

    bool init(Entity* player, Entity& final_boss, std::list<Entity> *entities, vec2 screen_bounds, FinalBossSpawningSystem* final_boss_spawning_system);

    void update(Entity& final_boss, float ms);

private:

    void phase_1 (Entity& final_boss, float ms);
    void phase_2 (Entity& final_boss, float ms);
    void phase_2a (Entity& final_boss, float ms);
    void phase_2b (Entity& final_boss, float ms);
    void phase_3 (Entity& final_boss, float ms);

    void move_to_start_pos(Entity& final_boss);


    int m_final_boss_max_health;

    float m_boss_move_speed;

    float m_phase_1_timer;
    float m_phase_1_frequency;

    float m_phase_1_minion_spawn_timer;
    float m_phase_1_minion_spawn_frequency;
    float m_phase_1_minion_timer;
    float m_phase_1_minion_frequency;
    bool m_spawning_minions;
    int m_minions_to_spawn;
    int m_minions_spawned;


    float m_phase_2a_timer;
    float m_phase_2a_frequency;
    float m_phase_2b_timer;
    float m_phase_2b_frequency;

    int m_phase_2_count;
    int m_phase_2_frequency;
    bool m_phase_2a;

    vec2 m_screen_bounds;
    vec2 m_start_pos;

    std::list<Entity>* m_entities;
    Entity* m_player;

    FinalBossSpawningSystem* m_final_boss_spawning_system;
};

#endif //DAB_FINAL_BOSS_SYSTEM_HPP
