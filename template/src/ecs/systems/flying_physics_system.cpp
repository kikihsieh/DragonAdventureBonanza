#include <cmath>
#include <ecs/systems/default_physics_system.hpp>
#include "flying_physics_system.hpp"

bool FlyingPhysicsSystem::init(std::list<Entity> *entities, vec2 level_bounds) {
    m_entities = entities;

    m_level_bounds_x = {0, level_bounds.x};
    m_level_bounds_y = {0, level_bounds.y};

    return true;
}

void FlyingPhysicsSystem::update(float ms) {
    auto entity_it = m_entities->begin();
    while (entity_it != m_entities->end()) {

        if (!entity_it->physics || entity_it->clipped) {
            entity_it++;
            continue;
        }

        float friction = (entity_it->physics->grounded) ? 500 : 300;
        friction = friction * ms / 1000;

        if (entity_it->input) {
            if (entity_it->input->right) {
                entity_it->is_facing_forward = true;
                entity_it->physics->velocity.x = entity_it->physics->walk_speed;
            }
            if (entity_it->input->left) {
                entity_it->is_facing_forward = false;
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

        if ((entity_it->is_player_proj || entity_it->is_enemy_proj) && entity_it->clipped) {
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
            return;
        }
        if (entity.physics->velocity.x > 0 && entity.position.x + width / 2 + x_buffer> m_level_bounds_x.y) {
            return;
        }
        if (entity.physics->velocity.y < 0 && entity.position.y - height / 2 - y_buffer < m_level_bounds_y.x) {
            return;
        }
        if (entity.physics->velocity.y > 0 && entity.position.y + height / 2 + y_buffer > m_level_bounds_y.y) {
            return;
        }
    }

    entity.physics->velocity.x += (entity.physics->acceleration.x * ms / 1000);
    entity.physics->velocity.y += (entity.physics->acceleration.y * ms / 1000);

    float x_step = entity.physics->velocity.x * (ms / 1000);
    float y_step = entity.physics->velocity.y * (ms / 1000);

    if (entity.physics->velocity.x < 0 && entity.position.x + width / 2 < m_level_bounds_x.x) {
        x_step = 0;
        if (!entity.player_tag) entity.clipped = true;
    }
    if (entity.physics->velocity.x > 0 && entity.position.x - width / 2 > m_level_bounds_x.y) {
        x_step = 0;
        if (!entity.player_tag) entity.clipped = true;
    }
    if (entity.physics->velocity.y < 0 && entity.position.y + height / 2 < m_level_bounds_y.x) {
        y_step = 0;
        if (!entity.player_tag) entity.clipped = true;
    }

    entity.position.x += x_step;
    entity.position.y += y_step;
}