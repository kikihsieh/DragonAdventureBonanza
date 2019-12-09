#include <cmath>
#include <ecs/systems/default_physics_system.hpp>
#include "world.hpp"

DefaultPhysicsSystem::DefaultPhysicsSystem(bool double_jump) {
    m_double_jump = double_jump;
}


bool DefaultPhysicsSystem::init(std::list<Entity> *entities, vec2 level_bounds) {
    m_entities = entities;

    m_level_bounds_x = {0, level_bounds.x};
    m_level_bounds_y = {0, level_bounds.y};

    return true;
}


void DefaultPhysicsSystem::update(float ms) {
    auto entity_it = m_entities->begin();
    while (entity_it != m_entities->end()) {

        if ((entity_it->is_player_proj || entity_it->is_enemy_proj) && entity_it->clipped) {
            entity_it->destroy();
            entity_it = m_entities->erase(entity_it);
            continue;
        }

        if (!entity_it->physics || entity_it->clipped) {
            entity_it++;
            continue;
        }

        float max_friction = 4;
        float friction = (entity_it->physics->grounded_friction || entity_it->physics->leaving_ice) ? entity_it->physics->grounded_friction : max_friction;

        if (entity_it->input) {
            if (!entity_it->airdash || !entity_it->airdash->airdashing) {
                if (entity_it->input->right) {
                    entity_it->is_facing_forward = true;
                    entity_it->physics->velocity.x += 20 * friction * ms;
                } else if (entity_it->input->left) {
                    entity_it->is_facing_forward = false;
                    entity_it->physics->velocity.x -= 20 * friction * ms;
                } else {
                    if (entity_it->physics->leaving_ice) {
                        entity_it->physics->velocity.x *= (1.f - (ms * 0.001f));
                    } else if (entity_it->physics->grounded) {
                        entity_it->physics->velocity.x *= 1.012f * pow(1 - friction / max_friction, ms);
                    } else {
                         entity_it->physics->velocity.x *= (1.f - (ms * 0.01f));
                    }

                    if (entity_it->physics->velocity.x > -entity_it->physics->walk_speed * 0.05 &&
                        entity_it->physics->velocity.x < entity_it->physics->walk_speed * 0.05)
                        entity_it->physics->velocity.x = 0;
                }
                if (entity_it->input->up) {
                    if (entity_it->physics->jump_count < ((m_double_jump)? 2 : 1)) {
                        entity_it->physics->velocity.y = entity_it->physics->jump_speed;
                        entity_it->physics->leaving_ice = false;
                        entity_it->physics->jump_count++;
                        
                        World::playSFX(World::JUMP);

                        // Holding down up arrow will cause the player to jump twice in very quick succession
                        // This will appear as a single jump
                        // Set up to false so this doesnt occur
                        entity_it->input->up = false;
                    }
                }

                if (entity_it->physics->velocity.x > entity_it->physics->walk_speed + (entity_it->physics->grounded_friction * 15000))
                    entity_it->physics->velocity.x = entity_it->physics->walk_speed + (entity_it->physics->grounded_friction * 15000);
                if (entity_it->physics->velocity.x < -entity_it->physics->walk_speed - (entity_it->physics->grounded_friction * 15000))
                    entity_it->physics->velocity.x = -entity_it->physics->walk_speed - (entity_it->physics->grounded_friction * 15000);
            }
        }

        move(ms, *entity_it);

        if (entity_it->position.y > m_level_bounds_y.y) {
            entity_it->physics->off_screen = true;
        }

        entity_it++;
    }
}

void DefaultPhysicsSystem::move(float ms, Entity& entity) {
    entity.physics->velocity.x += (entity.physics->acceleration.x * ms / 1000);
    entity.physics->velocity.y += (entity.physics->acceleration.y * ms / 1000);

    float x_step = entity.physics->velocity.x * (ms / 1000);
    float y_step = entity.physics->velocity.y * (ms / 1000);

    float width = entity.texture_size.x * entity.scale.x;
    float height = entity.texture_size.y * entity.scale.y;

    if (entity.physics->velocity.x < 0 && entity.position.x - width / 2 < m_level_bounds_x.x) {
        x_step = 0;
        if (entity.is_enemy_proj || entity.is_player_proj) entity.clipped = true;
    }
    if (entity.physics->velocity.x > 0 && entity.position.x + width / 2 > m_level_bounds_x.y) {
        x_step = 0;
        if (entity.is_enemy_proj || entity.is_player_proj) entity.clipped = true;
    }
    if (entity.physics->velocity.y < 0 && entity.position.y - height / 2 < m_level_bounds_y.x) {
        y_step = 0;
        if (entity.is_enemy_proj || entity.is_player_proj) entity.clipped = true;
    }

    if (entity.position.y - height / 2 > m_level_bounds_y.y) {
        if (entity.is_enemy_proj || entity.is_player_proj) entity.clipped = true;
    }

    entity.position.x += x_step;
    entity.position.y += y_step;
}
