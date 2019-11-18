#include "physics_system.hpp"

#include <cmath>

bool PhysicsSystem::init(std::list<Entity> *entities, vec2 level_bounds) {
    m_entities = entities;

    m_level_bounds_x = {0, level_bounds.x};
    m_level_bounds_y = {0, level_bounds.y};

    return true;
}

void PhysicsSystem::update(float ms) {
    auto entity_it = m_entities->begin();
    while (entity_it != m_entities->end()) {

        if (!entity_it->physics || entity_it->clipped) {
            entity_it++;
            continue;
        }

        float friction = (entity_it->physics->grounded) ? 1200 : 300;
        friction = friction * ms / 1000;

        if (entity_it->input) {
          if (!entity_it->airdash || !entity_it->airdash->airdashing) {
            if (entity_it->input->right) {
                entity_it->is_facing_forward = true;
                if (entity_it->physics->velocity.x < entity_it->physics->walk_speed) {
                    entity_it->physics->velocity.x = fmin(entity_it->physics->walk_speed, entity_it->physics->velocity.x + friction + 40);
                } else {
                    entity_it->physics->velocity.x = fmax(entity_it->physics->walk_speed, entity_it->physics->velocity.x - friction);
                }
            } else if (entity_it->input->left) {
                entity_it->is_facing_forward = false;
                if (entity_it->physics->velocity.x > entity_it->physics->walk_speed) {
                    entity_it->physics->velocity.x = fmax(-entity_it->physics->walk_speed,
                                                          entity_it->physics->velocity.x - friction - 40);
                } else {
                    entity_it->physics->velocity.x = fmin(-entity_it->physics->walk_speed,
                                                          entity_it->physics->velocity.x + friction);

                }
            } else {
                if (entity_it->is_facing_forward) {
                    entity_it->physics->velocity.x = fmax(0, entity_it->physics->velocity.x - friction);
                } else {
                    entity_it->physics->velocity.x = fmin(0, entity_it->physics->velocity.x + friction);
                }
            }
            if (entity_it->input->up) {
                if (entity_it->physics->jump_count < 2) {
                    entity_it->physics->velocity.y = entity_it->physics->jump_speed;
                    entity_it->physics->jump_count++;

                    // Holding down up arrow will cause the player to jump twice in very quick succession
                    // This will appear as a single jump
                    // Set up to false so this doesnt occur
                    entity_it->input->up = false;
                }
            }
          }
        }

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

void PhysicsSystem::move(float ms, Entity& entity) {
    entity.physics->velocity.x += (entity.physics->acceleration.x * ms / 1000);
    entity.physics->velocity.y += (entity.physics->acceleration.y * ms / 1000);

    float x_step = entity.physics->velocity.x * (ms / 1000);
    float y_step = entity.physics->velocity.y * (ms / 1000);

    if (entity.physics->velocity.x < 0 && entity.position.x < m_level_bounds_x.x) {
        x_step = 0;
        if (!entity.player_tag) entity.clipped = true;
    }
    if (entity.physics->velocity.x > 0 && entity.position.x > m_level_bounds_x.y) {
        x_step = 0;
        if (!entity.player_tag) entity.clipped = true;
    }
    if (entity.physics->velocity.y < 0 && entity.position.y < m_level_bounds_y.x) {
        y_step = 0;
        if (!entity.player_tag) entity.clipped = true;
    }

    entity.position.x += x_step;
    entity.position.y += y_step;
}
