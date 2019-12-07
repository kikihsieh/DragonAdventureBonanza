#include <ecs/systems/final_boss_system.hpp>
#include <vector>

bool FinalBossSystem::init(Entity* player, Entity& final_boss, std::list<Entity> *entities, vec2 screen_size,
        FinalBossSpawningSystem* final_boss_spawning_system, std::function<void(void)> scene_change_callback,
        bool* draw_level_intro) {

    m_draw_level_intro = draw_level_intro;

    m_scene_change_callback = scene_change_callback;
    m_entities = entities;
    m_player = player;

    m_boss_move_speed = 100;

    m_phase_1_timer = 0;
    m_phase_1_frequency = 3000;
    m_phase_1_minion_spawn_timer = 0;
    m_phase_1_minion_spawn_frequency = 5000;
    m_spawning_minions = false;
    m_minions_to_spawn = 3;
    m_minions_spawned = 0;
    m_phase_1_minion_frequency = 500;
    m_phase_1_minion_timer = m_phase_1_minion_frequency;

    m_phase_2a_timer = 0;
    m_phase_2a_frequency = 2000;
    m_phase_2b_timer = 0;
    m_phase_2b_frequency = 1500;
    m_phase_2_count = 0;
    m_phase_2_frequency = 5;
    m_phase_2a = true;

    m_phase_3_timer = 0;
    m_phase_3_frequency = 700;
    m_phase_3a = true;

    m_phase_4_timer = 0;
    m_phase_4_frequency = 400;
    m_last_safe_y = screen_size.y / 2;
    m_phase_4_count = 0;

    m_death_delay = 3000;
    m_death_timer = 0;
    m_death = false;

    final_boss.physics->velocity.y = m_boss_move_speed;
    m_final_boss_max_health = final_boss.health->health;

    m_screen_bounds = screen_size;

    m_final_boss_spawning_system = final_boss_spawning_system;
    m_start_pos = final_boss.position;

    return true;
}

void FinalBossSystem::update(Entity& final_boss, float ms) {

    if (*m_draw_level_intro)
        return;

    if (m_player->position.x > 800)
        m_player->position.x = 800;

    if (final_boss.health->health > m_final_boss_max_health * 0.8)
        phase_1(final_boss, ms);
    else if (final_boss.health->health > m_final_boss_max_health * 0.55) {
        if (len(sub(final_boss.position, m_start_pos)) > 10)
            move_to_start_pos(final_boss);
        else
            phase_2(final_boss, ms);
    } else if (final_boss.health->health > m_final_boss_max_health * 0.4) {
        if (len(sub(final_boss.position, m_start_pos)) > 10)
            move_to_start_pos(final_boss);
        else
            phase_3(final_boss, ms);
        m_phase_2a_timer = 0;
        m_phase_2b_timer = 0;
        m_phase_2_count = 0;
        m_phase_2a = true;
    }else if (final_boss.health->health > m_final_boss_max_health * 0.3) {
        if (len(sub(final_boss.position, m_start_pos)) > 10)
            move_to_start_pos(final_boss);
        else
            phase_2(final_boss, ms);
    } else if (final_boss.health->health > 0) {
        if (len(sub(final_boss.position, m_start_pos)) > 10)
            move_to_start_pos(final_boss);
        else
            phase_4(final_boss, ms);
    } else {
        if (!m_death) {
            m_death_timer += ms;

            if (m_death_timer > m_death_delay)
                m_death = true;
        }
        if (m_death) {

            final_boss.health->invincibility_duration = 10000;
            final_boss.health->invincible = true;

            if (final_boss.scale.x > 0 && final_boss.scale.y > 0) {
                final_boss.scale.x -= 0.0005;
                final_boss.scale.y -= 0.005;

                if (final_boss.scale.x < 0)
                    final_boss.scale.x = 0;
                if (final_boss.scale.y < 0)
                    final_boss.scale.y = 0;
            } else {
                m_scene_change_callback();
            }
        }
    }

    m_entities->sort([](const Entity & a, const Entity & b) { return a.depth > b.depth;});
}

void FinalBossSystem::phase_1(Entity& final_boss, float ms) {

    float height = final_boss.texture_size.y * final_boss.scale.y + 50;
    float buffer = 50;

    if (final_boss.position.y - height / 2 <= 0 - buffer || final_boss.position.y + height / 2 >= m_screen_bounds.y + buffer) {
        final_boss.physics->velocity.y = -1 * final_boss.physics->velocity.y;
    }

    m_phase_1_timer += ms;

    if (m_phase_1_timer >= m_phase_1_frequency) {
        m_phase_1_timer = 0;

        float width = final_boss.texture_size.x * final_boss.scale.x + 50;
        m_final_boss_spawning_system->spawn_bomb(sub(final_boss.position, {width / 2 - 100, 0}));
    }

    if (!m_spawning_minions)
        m_phase_1_minion_spawn_timer += ms;

    if (m_phase_1_minion_spawn_timer >= m_phase_1_minion_spawn_frequency) {
        m_spawning_minions = true;
        m_phase_1_minion_spawn_timer = 0;
    }

    if (m_spawning_minions) {
        m_phase_1_minion_timer += ms;

        if (m_phase_1_minion_timer >= m_phase_1_minion_frequency) {
            m_phase_1_minion_timer = 0;
            m_final_boss_spawning_system->spawn_minion({m_screen_bounds.x, m_player->position.y}, {-1.5, 0}, 3);
            m_minions_spawned++;
        }
    }

    if (m_minions_spawned >= m_minions_to_spawn) {
        m_minions_spawned = 0;
        m_spawning_minions = false;
    }
}


void FinalBossSystem::phase_2(Entity& final_boss, float ms) {

    final_boss.physics->velocity = {0, 0};
    if (m_phase_2a)
        phase_2a(final_boss, ms);
    else
        phase_2b(final_boss, ms);

    if (m_phase_2_count >= m_phase_2_frequency) {
        m_phase_2_count = 0;
        m_phase_2a = !m_phase_2a;
    }
}

void FinalBossSystem::phase_2a(Entity& final_boss, float ms) {

    m_phase_2a_timer += ms;

    if (m_phase_2a_timer >= m_phase_2a_frequency) {
        m_phase_2a_timer = 0;
        m_phase_2_count++;

        float width = final_boss.texture_size.x * final_boss.scale.x + 50;
        m_final_boss_spawning_system->spawn_wave(sub(final_boss.position, {width / 2 - 100, 0}));
    }
}

void FinalBossSystem::phase_2b(Entity& final_boss, float ms) {

    m_phase_2b_timer += ms;

    if (m_phase_2b_timer >= m_phase_2b_frequency) {
        m_phase_2b_timer = 0;
        m_phase_2_count++;

        float width = final_boss.texture_size.x * final_boss.scale.x + 50;
        m_final_boss_spawning_system->spawn_wall(sub(final_boss.position, {width / 2 - 100, 0}));
    }
}

void FinalBossSystem::phase_3(Entity& final_boss, float ms) {

    final_boss.physics->velocity = {0, 0};
    m_phase_2a = true;

    m_phase_3_timer += ms;

    if (m_phase_3_timer > m_phase_3_frequency) {
        m_phase_3a = !m_phase_3a;
        m_phase_3_timer = 0;

        float offset;
        if (m_phase_3a)
            offset = 0;
        else
            offset = 0.26 / 2;

        float width = final_boss.texture_size.x * final_boss.scale.x + 50;
        m_final_boss_spawning_system->spawn_radial(sub(final_boss.position, {width / 2 - 100, 0}), offset);
    }
}

void FinalBossSystem::phase_4(Entity& final_boss, float ms) {

    final_boss.physics->velocity = {0, 0};

    m_phase_4_timer += ms;

    if (m_phase_4_timer > m_phase_4_frequency) {
        m_phase_4_timer = 0;

        float width = final_boss.texture_size.x * final_boss.scale.x + 50;
        m_phase_4_count++;
        if (m_phase_4_count > 4)
            m_phase_4_count = 0;

        m_last_safe_y = m_final_boss_spawning_system->spawn_maze(sub(final_boss.position, {width / 2 - 100, 0}), m_last_safe_y, m_phase_4_count);
    }
}

void FinalBossSystem::move_to_start_pos(Entity &final_boss) {
    vec2 dir = normalize(sub(m_start_pos, final_boss.position));
    final_boss.physics->velocity = mul(dir, 4 * m_boss_move_speed);
}