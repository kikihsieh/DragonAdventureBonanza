#include "physics_system.hpp"

#include <cmath>
#include <utility>
#include <scenes/levels/tile_map.hpp>

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

        vec2 old_position = entity.position;

        move(ms, entity);

        if (entity.collider) {
            tile_collisions(entity);
            entity_collisions(entity);
            if (entity.collider->left || entity.collider->right) {
                entity.position.x = old_position.x;
            }
            if (entity.collider->top || entity.collider->bottom) {
                entity.position.y = old_position.y;
                entity.physics->velocity.y = 0;
            }
        }
    }
}

bool PhysicsSystem::init(std::list<Entity> *entities, const std::map<int, Tile*>& tiles) {
    m_entities = entities;
    m_tiles = tiles;

    return true;
}

void PhysicsSystem::tile_collisions(Entity& entity) {
    entity.collider->reset();
    float e_height = entity.drawable->texture->height * entity.scale.x;
    float e_width = entity.drawable->texture->width * entity.scale.y;

    float t_width = TileMap::tile_screen_size.x;
    float t_height = TileMap::tile_screen_size.y;

    std::pair<int, int> tile_pos = TileMap::get_tile_pos_from_coord(entity.position.x, entity.position.y, {e_width, e_height});

    for (int col = tile_pos.first; col <= tile_pos.first + ceil(e_width / t_width); col++) {
        for (int row = tile_pos.second; row <= tile_pos.second + ceil(e_height / t_height); row++) {
            if (!m_tiles.count(TileMap::hash(col, row))) {
                continue;
            }
            Tile* tile = m_tiles.at(TileMap::hash(col, row));
            collide(entity, *tile);
        }
    }
}

void PhysicsSystem::entity_collisions(Entity& entity) {
    // TODO: implement collisions between other entities
}

void PhysicsSystem::move(float ms, Entity& entity) {
    entity.physics->velocity.x += entity.physics->acceleration.x;
    entity.physics->velocity.y += entity.physics->acceleration.y;

    float x_step = entity.physics->velocity.x * (ms / 1000);
    float y_step = entity.physics->velocity.y * (ms / 1000);

    entity.position.x += x_step;
    entity.position.y += y_step;
}

void PhysicsSystem::collide(Entity &e1, Entity &e2) {
    float e1_height = e1.drawable->texture->height * e1.scale.x;
    float e1_width = e1.drawable->texture->width * e1.scale.y;

    float e2_height = e2.drawable->texture->height * e2.scale.x;
    float e2_width = e2.drawable->texture->width * e2.scale.y;

//    https://stackoverflow.com/questions/29861096/detect-which-side-of-a-rectangle-is-colliding-with-another-rectangle
    float dx = e1.position.x - e2.position.x;
    float dy = e1.position.y - e2.position.y;
    float width = (e1_width + e2_width)/2;
    float height = (e1_height + e2_height)/2;
    float crossWidth = width*dy;
    float crossHeight = height*dx;

    if (abs(dx) <= width && abs(dy) <= height){
        if(crossWidth > crossHeight){
            if (crossWidth > -crossHeight) {
                e1.collider->bottom = true;
                if (e2.collider) {
                    e2.collider->top = true;
                }
            } else {
                e1.collider->left = true;
                if (e2.collider) {
                    e2.collider->right = true;
                }
            }
        } else {
            if (crossWidth > -crossHeight) {
                e1.collider->right = true;
                if (e2.collider) {
                    e2.collider->left = true;
                }
            } else {
                e1.collider->top = true;

                if (e1.airdash)
                    e1.airdash->can_airdash = true;

                if (e2.collider) {
                    e2.collider->bottom = true;
                }

                if (e1.physics) {
                    e1.physics->jump_count = 0;
                }
            }
        }
    }
}
