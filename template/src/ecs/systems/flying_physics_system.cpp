#include <ecs/systems/default_physics_system.hpp>
#include "flying_physics_system.hpp"
#include "final_boss_spawning_system.hpp"

bool FlyingPhysicsSystem::init(std::list<Entity> *entities, vec2 level_bounds) {
    m_entities = entities;

    m_level_bounds_x = {0, level_bounds.x};
    m_level_bounds_y = {0, level_bounds.y};

    return true;
}

void FlyingPhysicsSystem::update(float ms) {

    auto entity_it = m_entities->begin();
    while (entity_it != m_entities->end()) {

        if (!entity_it->physics) { // || entity_it->clipped) {
            entity_it++;
            continue;
        }

        if (entity_it->input) {
            if (entity_it->input->right) {
                entity_it->is_facing_forward = true;
                entity_it->physics->velocity.x = entity_it->physics->walk_speed;
            }
            if (entity_it->input->left) {
                // Want the player to always be shooting forwards
                // Render system hasnt changed yet, but that player sprite should also always face forwards
                entity_it->is_facing_forward = true;
                entity_it->physics->velocity.x = -entity_it->physics->walk_speed;
            }
            if (entity_it->input->up) {
                entity_it->physics->velocity.y = -entity_it->physics->walk_speed;
            }
            if (entity_it->input->down) {
                entity_it->physics->velocity.y = entity_it->physics->walk_speed;
            }
        }

        if (entity_it->player_tag)
            entity_it->physics->velocity = mul(entity_it->physics->velocity, 0.8);

        move(ms, *entity_it);

        if (entity_it->position.y > m_level_bounds_y.y) {
            entity_it->physics->off_screen = true;
        }

        float buffer = 10;
        if (entity_it->is_bomb && entity_it->position.x - (entity_it->texture_size.x * entity_it->scale.x) / 2 - buffer <= 0) {
            m_final_boss_spawning_system->explode_bomb(entity_it->position);
            entity_it->destroy();
            entity_it = m_entities->erase(entity_it);
            continue;
        }

        if (entity_it->clipped) {
            entity_it->destroy();
            entity_it = m_entities->erase(entity_it);
            continue;
        }
        entity_it++;
    }
}

void FlyingPhysicsSystem::move(float ms, Entity& entity) {

    float width = entity.texture_size.x * entity.scale.x;
    float height = entity.texture_size.y * entity.scale.y;

    if (entity.player_tag) {
        float x_buffer = 5;
        float y_buffer = 10;

        if (entity.physics->velocity.x < 0 && entity.position.x - width / 2 - x_buffer< m_level_bounds_x.x) {
            entity.physics->velocity.x = 0;
        }
        if (entity.physics->velocity.x > 0 && entity.position.x + width / 2 + x_buffer> m_level_bounds_x.y) {
            entity.physics->velocity.x = 0;
        }
        if (entity.physics->velocity.y < 0 && entity.position.y - height / 2 - y_buffer < m_level_bounds_y.x) {
            entity.physics->velocity.y = 0;
        }
        if (entity.physics->velocity.y > 0 && entity.position.y + height / 2 + y_buffer > m_level_bounds_y.y) {
            entity.physics->velocity.y = 0;
        }
    }

    entity.physics->velocity.x += (entity.physics->acceleration.x * ms / 1000);
    entity.physics->velocity.y += (entity.physics->acceleration.y * ms / 1000);

    float x_step = entity.physics->velocity.x * (ms / 1000);
    float y_step = entity.physics->velocity.y * (ms / 1000);
    float buffer = 25;

    if (entity.position.x + width / 2 + buffer < m_level_bounds_x.x) {
        if (entity.is_player_proj || entity.is_enemy_proj || entity.is_boss_proj || entity.is_minion) {
            entity.clipped = true;
            return;
        }
    }
    if (entity.position.x - width / 2 - buffer > m_level_bounds_x.y) {
        if (entity.is_player_proj || entity.is_enemy_proj || entity.is_boss_proj || entity.is_minion) {
            entity.clipped = true;
            return;
        }
    }
    if (entity.position.y + height / 2 + buffer < m_level_bounds_y.x) {
        if (entity.is_player_proj || entity.is_enemy_proj || entity.is_boss_proj || entity.is_minion) {
            entity.clipped = true;
            return;
        }
    }
    if (entity.position.y - height / 2  - buffer > m_level_bounds_y.y) {
        if (entity.is_player_proj || entity.is_enemy_proj || entity.is_boss_proj || entity.is_minion) {
            entity.clipped = true;
            return;
        }
    }

    entity.position.x += x_step;
    entity.position.y += y_step;
}


void FlyingPhysicsSystem::set_spawning_system(FinalBossSpawningSystem* final_boss_spawning_system) {
    m_final_boss_spawning_system = final_boss_spawning_system;
}