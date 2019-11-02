#include "collision_system.hpp"

#include <cmath>
#include <utility>
#include <scenes/levels/tile_map.hpp>
#include "iostream"

void CollisionSystem::update(float ms) {
    for (auto &entity : *m_entities) {
        if (!entity.collider) {
            continue;
        }

        for (auto &e : *m_entities) {
            if (e.collider) {
                e.collider->reset();
            }
        }
        if (entity.collider) {
            tile_collisions(entity);
            entity_collisions(entity);
            if (entity.collider->left || entity.collider->right) {
                entity.position.x = entity.old_position.x;
            }
            if (entity.collider->top || entity.collider->bottom) {
                entity.position.y = entity.old_position.y;
                entity.physics->velocity.y = 0;
            }
        }
    }
}

bool CollisionSystem::init(std::list<Entity> *entities, const std::map<int, Tile*>& tiles) {
    m_entities = entities;
    m_tiles = tiles;

    return true;
}

void CollisionSystem::tile_collisions(Entity& entity) {
    float e_height = entity.drawable->texture->height * entity.scale.x;
    float e_width = entity.drawable->texture->width * entity.scale.y;

    float t_width = TileMap::tile_screen_size.x;
    float t_height = TileMap::tile_screen_size.y;

    std::pair<int, int> tile_pos = TileMap::get_tile_pos_from_coord(entity.position.x, entity.position.y, {e_width, e_height});

    bool collided = false;

    for (int col = tile_pos.first; col <= tile_pos.first + ceil(e_width / t_width); col++) {
        for (int row = tile_pos.second; row <= tile_pos.second + ceil(e_height / t_height); row++) {
            if (!m_tiles.count(TileMap::hash(col, row))) {
                continue;
            }

            Tile* tile = m_tiles.at(TileMap::hash(col, row));
            if(collide(entity, *tile))
                collided = true;
        }
    }

    if (!collided && entity.health && entity.health->is_player)
        fall(entity);
}

void CollisionSystem::entity_collisions(Entity& entity) {
    // TODO: implement collisions between other entities
    //      May need to add id to entities or something to make sure it doesn't check against itself
}

/**
 * This function expects that the first entity is collidable
 * @param e1 : a collidable entity
 * @param e2 : any entity
 */
bool CollisionSystem::collide(Entity &e1, Entity &e2) {
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

                if (e2.collider) {
                    e2.collider->bottom = true;
                }

                land(e1);
                return true;
            }
        }
    }

    return false;
}

void CollisionSystem::land(Entity &entity) {
    if (entity.airdash)
        entity.airdash->can_airdash = true;

    if (entity.physics) {
        entity.physics->jump_count = 0;
        entity.physics->grounded = true;
    }
}

void CollisionSystem::fall(Entity &entity) {
    if (entity.physics) {
        entity.physics->grounded = false;
    }
}