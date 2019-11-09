#include "physics_system.hpp"

#include <cmath>
#include <utility>
#include <iostream>

void PhysicsSystem::update(float ms) {
    for (auto &entity : *m_entities) {
        if (!entity.physics) {
            continue;
        }

        if (entity.input) {
          if (!entity.airdash || !entity.airdash->airdashing) {
            if (entity.input->right) {
                entity.is_facing_forward = true;
                entity.physics->velocity.x = entity.physics->walk_speed;
            } else if (entity.input->left) {
                entity.is_facing_forward = false;
                entity.physics->velocity.x = -1 * entity.physics->walk_speed;
            } else {
                entity.physics->velocity.x = 0;
            }
            if (entity.input->up) {
                if (entity.physics->jump_count < 2) {
                    entity.physics->velocity.y = entity.physics->jump_speed;
                    entity.physics->jump_count++;

                    // Holding down up arrow will cause the player to jump twice in very quick succession
                    // This will appear as a single jump
                    // Set up to false so this doesnt occur
                    entity.input->up = false;
                }
            }
          }
        }
        
        entity.old_position = entity.position;

        move(ms, entity);

        if (entity.position.y > m_level_bounds_y.y) {
            // Fall off screen handler. Requires health
        }
    }
}

bool PhysicsSystem::init(std::list<Entity> *entities, vec2 level_bounds) {
    m_entities = entities;

    m_level_bounds_x = {0, level_bounds.x};
    m_level_bounds_y = {0, level_bounds.y};

    return true;
}

void PhysicsSystem::move(float ms, Entity& entity) {
    entity.physics->velocity.x += (entity.physics->acceleration.x * ms / 1000);
    entity.physics->velocity.y += (entity.physics->acceleration.y * ms / 1000);

    float x_step = entity.physics->velocity.x * (ms / 1000);
    float y_step = entity.physics->velocity.y * (ms / 1000);

    if (!entity.is_player_proj || !entity.is_enemy_proj) {
        if (entity.physics->velocity.x < 0 && entity.position.x < m_level_bounds_x.x)
            x_step = 0;
        if (entity.physics->velocity.x > 0 && entity.position.x > m_level_bounds_x.y)
            x_step = 0;
        if (entity.physics->velocity.y < 0 && entity.position.y < m_level_bounds_y.x) {
            y_step = 0;
            entity.physics->velocity.y = 0;
        }
    }

    entity.position.x += x_step;
    entity.position.y += y_step;
    
    //std::cout << entity.position.x << ", " << entity.position.y << std::endl;
}
