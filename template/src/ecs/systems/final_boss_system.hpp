#ifndef DAB_FINAL_BOSS_SYSTEM_HPP
#define DAB_FINAL_BOSS_SYSTEM_HPP

#include <functional>
#include <ecs/entities/entity.hpp>
#include <list>
#include "final_boss_spawning_system.hpp"

class FinalBossSystem {
public:
    bool init(Entity* player, Entity& final_boss, std::list<Entity> *entities, vec2 screen_bounds,
            FinalBossSpawningSystem* final_boss_spawning_system, std::function<void(void)> scene_change_callback,
            bool* draw_level_intro);

    void update(Entity& final_boss, float ms);

private:

    void phase_1 (Entity& final_boss, float ms);
    void phase_2 (Entity& final_boss, float ms);
    void phase_2a (Entity& final_boss, float ms);
    void phase_2b (Entity& final_boss, float ms);
    void phase_3 (Entity& final_boss, float ms);
    void phase_4 (Entity& final_boss, float ms);

    void move_to_start_pos(Entity& final_boss);

    bool* m_draw_level_intro;

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

    float m_phase_3_timer;
    float m_phase_3_frequency;
    bool m_phase_3a;

    float m_phase_4_timer;
    float m_phase_4_frequency;
    float m_last_safe_y;
    int m_phase_4_count;

    float m_death_delay;
    float m_death_timer;
    bool m_death;

    vec2 m_screen_bounds;
    vec2 m_start_pos;

    std::list<Entity>* m_entities;
    Entity* m_player;

    FinalBossSpawningSystem* m_final_boss_spawning_system;

    std::function<void(void)> m_scene_change_callback;
};

#endif //DAB_FINAL_BOSS_SYSTEM_HPP
