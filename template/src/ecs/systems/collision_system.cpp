#include "collision_system.hpp"

#include <cmath>
#include <utility>
#include <scenes/levels/tile_map.hpp>

bool CollisionSystem::init(std::list<Entity> *entities, std::map<int, Tile*>* tiles) {
    m_entities = entities;
    m_tiles = tiles;

    return true;
}

void CollisionSystem::update(float ms) {
    auto entity_it = m_entities->begin();
    while (entity_it != m_entities->end()) {

        if (!entity_it->collider || entity_it->clipped) {
            entity_it++;
            continue;
        }

        entity_it->collider->reset();

        if (collide_with_entities(*entity_it) && (entity_it->is_enemy_proj || entity_it->is_player_proj)) {
            entity_it->destroy();
            entity_it = m_entities->erase(entity_it);
            continue;
        }

        // IMPORTANT! entity collision checks need to come before tile collision check
        if (!entity_it->flyable) {
            tile_collisions(*entity_it, ms);
        }

        if (entity_it->properties && entity_it->properties->count <= 0) {
            entity_it->destroy();
            entity_it = m_entities->erase(entity_it);
            continue;
        }

        entity_it++;
    }
}

void CollisionSystem::tile_collisions(Entity& entity, float ms) {
    float e_height = entity.texture_size.y * entity.scale.y;
    float e_width = entity.texture_size.x * entity.scale.x;

    float t_width = TileMap::tile_screen_size.x;
    float t_height = TileMap::tile_screen_size.y;

    std::pair<int, int> tile_pos = TileMap::get_tile_pos_from_coord(entity.position.x, entity.position.y, {e_width, e_height});

    for (int col = tile_pos.first; col <= tile_pos.first + ceil(e_width / t_width); col++) {
        for (int row = tile_pos.second; row <= tile_pos.second + ceil(e_height / t_height); row++) {
            if (!m_tiles->count(TileMap::hash(col, row))) {
                continue;
            }

            Tile* tile = m_tiles->at(TileMap::hash(col, row));
            if (collide_with_tile(entity, *tile, ms) &&
                    tile->properties && tile->properties->type == Properties::COLLECTIBLE && entity.player_tag) {
                entity.health->increase_health();
                tile->destroy();
                m_tiles->erase(TileMap::hash(col, row));
            }
        }
    }

    if (entity.health && entity.health->is_player && !entity.collider->top)
        fall(entity);
}

bool CollisionSystem::collide_with_entities(Entity &e) {
    bool collided = false;
    auto entity_it = m_entities->begin();
    while (entity_it != m_entities->end()) {
        if (!entity_it->collider || entity_it->id == e.id) {
            ++entity_it;
            continue;
        }

        CollisionSystem::Side side = detect_collision(e, *entity_it);

        if (side == CollisionSystem::Side::NONE) {
            ++entity_it;
            continue;
        }

        if ((e.is_player_proj && entity_it->player_tag) || (!entity_it->player_tag && e.is_enemy_proj)) {
            ++entity_it;
            continue;
        }

        if (e.player_tag) {
            if (entity_it->is_player_proj) {
                ++entity_it;
                continue;
            }
            if (side == CollisionSystem::TOP) {
                e.physics->velocity.y = -200.f;
                land(e);

                if (entity_it->health) {
                    entity_it->health->decrease_health();
                }

            } else if (!e.health->invincible){
                e.health->decrease_health();
            }
        } else if (e.is_player_proj) {
            if (entity_it->health) {
                entity_it->health->decrease_health();
            }
            if (e.properties) {
                e.properties->count--;
            }
            return true;
        }
        collided = true;
        ++entity_it;
    }
    return collided;
}

/**
 * This function expects that the first entity is collidable
 * @param e1 : a collid-able entity
 * @param tile : a tile
 */
bool CollisionSystem::collide_with_tile(Entity& e1, Tile &tile, float ms) {
    float max_vel = 450;

    float e1_height = e1.texture_size.y * e1.scale.y * 0.5f;
    float e1_width = e1.texture_size.x * e1.scale.x * 0.5f;

    float t_height = tile.texture_size.y * tile.scale.y * 0.5f;
    float t_width = tile.texture_size.x * tile.scale.x * 0.5f;

    float hit_vel_y = e1.physics->velocity.y;
    // TODO: make it work when both tile and entity has properties
    //      also friction should use ms to update at the same rate
//    hit_vel_y = (tile.properties) ? -1.f * hit_vel_y * tile.properties->bounce : 0;
    hit_vel_y = (e1.properties) ? -1.f * hit_vel_y * e1.properties->bounce : hit_vel_y;

    float hit_vel_x = e1.physics->velocity.x;
    if (tile.properties)  {
        hit_vel_x = hit_vel_x * tile.properties->friction;
    }
    if (e1.properties)  {
        hit_vel_x = hit_vel_x * e1.properties->friction;
    }
    hit_vel_x = (e1.physics->velocity.x < 0) ?
                             fmin(max_vel, hit_vel_x) :
                             fmax(-max_vel, hit_vel_x);

    Side side = detect_collision(e1, tile);

    if (side == NONE || (tile.properties && tile.properties->type == Properties::DECORATION)) {
        return false;
    } else if (tile.properties && tile.properties->type == Properties::COLLECTIBLE && e1.player_tag) {
        return true;
    }

    switch (side) {
        case TOP: {
            e1.collider->top = true;
            e1.physics->velocity.y = fmin(e1.physics->velocity.y, hit_vel_y);
            e1.position.y = tile.position.y - t_height - e1_height - padding;
            land(e1);
            e1.physics->velocity.y = fmin(e1.physics->velocity.y, 0);
            e1.physics->velocity.x = hit_vel_x;
            grounded(e1);
            break;
        } case BOTTOM: {
            e1.collider->bottom = true;
            e1.physics->velocity.y = fmax(e1.physics->velocity.y, hit_vel_y);
            e1.position.y = tile.position.y + t_height + e1_height + padding;
            e1.physics->velocity.x = hit_vel_x;
            break;
        } case LEFT: {
            e1.collider->left = true;
            e1.position.x = tile.position.x + t_width + e1_width + padding;
            if (e1.properties) {
                e1.physics->velocity.x = -hit_vel_x;
            }
            break;
        } case RIGHT: {
            e1.collider->right = true;
            e1.position.x = tile.position.x - t_width - e1_width - padding;
            if (e1.properties) {
                e1.physics->velocity.x = -hit_vel_x;
            }
            break;
        } case NONE:
            return false;
    }
    if (e1.properties) {
        e1.properties->count--;
    }
    return true;
}

CollisionSystem::Side CollisionSystem::detect_collision(Entity &e1, Entity &e2) {
    float e1_height = e1.texture_size.y * e1.scale.y;
    float e1_width = e1.texture_size.x * e1.scale.x;

    float e2_height = e2.texture_size.y * e2.scale.y;
    float e2_width = e2.texture_size.x * e2.scale.x;

    // https://stackoverflow.com/questions/29861096/detect-which-side-of-a-rectangle-is-colliding-with-another-rectangle
    float dx = e1.position.x - e2.position.x;
    float dy = e1.position.y - e2.position.y;
    float width = (e1_width + e2_width)/2;
    float height = (e1_height + e2_height)/2;
    float crossWidth = width*dy;
    float crossHeight = height*dx;

    if (abs(dx) <= width && abs(dy) <= height){
        if(crossWidth > crossHeight){
            if (crossWidth > -crossHeight &&
                    (e2.position.y + (e2_height / 2.f)) < (e1.position.y - (e1_height / 3.f))) {
                return Side::BOTTOM;
            } else {
                return Side::RIGHT;
            }
        } else {
            if (crossWidth > -crossHeight) {
                return Side::LEFT;
            } else {
                return Side::TOP;
            }
        }
    }
    return Side::NONE;
}

void CollisionSystem::land(Entity &entity) {
    if (entity.airdash)
        entity.airdash->can_airdash = true;

    if (entity.physics) {
        entity.physics->jump_count = 0;
    }
}

void CollisionSystem::grounded(Entity &entity) {

    if (entity.physics) {
        land(entity);
        entity.physics->grounded = true;
    }
}

void CollisionSystem::fall(Entity &entity) {
    if (entity.physics) {
        entity.physics->grounded = false;
    }
}
