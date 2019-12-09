#include "collision_system.hpp"
#include <cmath>
#include <utility>
#include <scenes/levels/tile_map.hpp>
#include "world.hpp"
#define PI 3.141592653589793238463

bool CollisionSystem::init(std::list<Entity> *entities, std::map<int, Tile*>* tiles) {
    m_entities = entities;
    m_tiles = tiles;
    m_goal_reached = false;
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
    float e_height = abs(entity.texture_size.y * entity.scale.y);
    float e_width = abs(entity.texture_size.x * entity.scale.x);
    float t_width = TileMap::tile_screen_size.x;
    float t_height = TileMap::tile_screen_size.y;

    std::pair<int, int> tile_pos = TileMap::get_left_top_tile_pos_from_coord(entity.position.x, entity.position.y,
                                                                             {e_width, e_height});

    for (int col = tile_pos.first; col <= tile_pos.first + ceil(e_width / t_width); col++) {
        for (int row = tile_pos.second; row <= tile_pos.second + ceil(e_height / t_height); row++) {
            if (!m_tiles->count(TileMap::hash(col, row))) {
                continue;
            }

            Tile *tile = m_tiles->at(TileMap::hash(col, row));
            if (collide_with_tile(entity, *tile, ms)) {
                tile->destroy();
                m_tiles->erase(TileMap::hash(col, row));
            }
        }
    }

    if (entity.health && entity.health->is_player && !entity.collider->top)
        fall(entity);
}

bool CollisionSystem::tile_property_updates(Entity& entity, Tile& tile, Side side, float ms) {
    if (side == NONE) {
        return false;
    } else if (!tile.properties) {
        collider_updates(entity, tile, side);
        return entity_property_updates(entity, tile, side);
    }

    switch (tile.properties->type) {
        case Properties::TORCH_LIT:
            if (entity.is_player_proj)
                World::playSFX(World::TORCH);
            return false;
        case Properties::TORCH:
            if (entity.is_player_proj) {
                if (!tile.properties->lit) {
                    if (m_torches_to_light > 0)
                        m_torches_to_light--;
                    tile.properties->lit = true;
                    tile.drawable->texture = tile.torchTex;
                    tile.animatable->num_columns = 4;
                }
                World::playSFX(World::TORCH);
                return entity_property_updates(entity, tile, side);
            }
            return false;
        case Properties::DECORATIVE:
            return false;
        case Properties::HEALTH:
            if (entity.player_tag) {
                World::playSFX(World::HEART);
                entity.health->increase_health();
                return true;
            }
            return false;
        case Properties::SLIPPERY: {
            collider_updates(entity, tile, side);
            friction_updates(entity, tile.properties->friction, side, ms);
            break;
        }
        case Properties::BOUNCY:
            bounce_updates(entity, tile.properties->bounce, side);
            collider_updates(entity, tile, side);
            break;
        case Properties::DAMAGE:
            if (entity.player_tag) {
                entity.health->decrease_health();
            }
            return false;
        case Properties::GOAL: {
            if (m_torches_to_light <= 0)
                m_goal_reached = true;
            return false;
        } default:
            break;
    }
    if (entity.properties) {
        collider_updates(entity, tile, side);
        return entity_property_updates(entity, tile, side);
    }

    return false;
}

void CollisionSystem::bounce_updates(Entity &entity, float bounce, Side side) {
    float max_vel = 800;
    if (side == Side::TOP) {
        entity.physics->velocity.y = fmax(-max_vel, -entity.physics->velocity.y*bounce);
        entity.physics->velocity.y = fmin(-entity.physics->jump_speed, entity.physics->velocity.y);
    } else if (side == Side::BOTTOM) {
        entity.physics->velocity.y = fmin(max_vel, -entity.physics->velocity.y*bounce);
        entity.physics->velocity.y = fmax(entity.physics->jump_speed, entity.physics->velocity.y);
    }
}

void CollisionSystem::friction_updates(Entity &entity, float friction, Side side, float ms) {
    if (side == Side::BOTTOM) {
        entity.physics->velocity.y = fmax(-0.1f * entity.physics->velocity.y, entity.physics->velocity.y);
        return;
    } else if (side != TOP) {
        return;
    }
    entity.physics->leaving_ice = true;
    entity.physics->grounded_friction = 0.01;
    entity.physics->velocity.y = fmin(-0.1f * entity.physics->velocity.y, entity.physics->velocity.y);
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

        if ((e.is_player_proj && entity_it->player_tag) ||
                (!entity_it->player_tag && e.is_enemy_proj) ||
                (e.is_player_proj && entity_it->is_boss_proj)) {
            ++entity_it;
            continue;
        }

        if (e.player_tag) {
            if (entity_it->is_player_proj) {
                ++entity_it;
                continue;
            }
            if (side == CollisionSystem::TOP && !entity_it->is_boss_proj && !entity_it->is_minion) {
                e.physics->velocity.y = -200.f;
                land(e);

                if (entity_it->health) {
                    World::playSFX(World::ENEMY_DAMAGE);
                    entity_it->health->decrease_health();
                }

            } else if (!e.health->invincible){
                if (!entity_it->clipped)
                    World::playSFX(World::P_DAMAGE);
                    e.health->decrease_health();
            }
        } else if (e.is_player_proj) {
            if (entity_it->health) {
                World::playSFX(World::ENEMY_DAMAGE2);
                entity_it->health->decrease_health();
            }
            if (e.properties) {
                e.properties->count--;
            }
            if (entity_it->is_enemy_proj) {
                entity_it->properties->count = 0;
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
 * @param entity : a collid-able entity
 * @param tile : a tile
 * Returns true if the entity should be removed from the entity list
 */
bool CollisionSystem::collide_with_tile(Entity& entity, Tile &tile, float ms) {
    Side side = detect_collision(entity, tile);

    if (tile.properties || entity.properties) {
        return tile_property_updates(entity, tile, side, ms);
    }

    collider_updates(entity, tile, side);
    switch (side) {
        case TOP:
            entity.physics->velocity.y = fmin(-0.1f * entity.physics->velocity.y, entity.physics->velocity.y);
            break;
        case BOTTOM:
            entity.physics->velocity.y = fmax(-0.1f * entity.physics->velocity.y, entity.physics->velocity.y);
            break;
        default:
            break;
    }

    return false;
}

void CollisionSystem::collider_updates(Entity &entity, Tile &tile, CollisionSystem::Side side) {
    float e1_height = entity.texture_size.y * entity.scale.y * 0.5f;
    float e1_width = entity.texture_size.x * entity.scale.x * 0.5f;

    float t_height = tile.texture_size.y * tile.scale.y * 0.5f;
    float t_width = tile.texture_size.x * tile.scale.x * 0.5f;

    switch (side) {
        case TOP: {
            entity.collider->top = true;
            entity.position.y = tile.position.y - t_height - e1_height - padding;
            grounded(entity);
            break;
        } case BOTTOM: {
            entity.collider->bottom = true;
            entity.position.y = tile.position.y + t_height + e1_height + padding;
            break;
        } case LEFT: {
            entity.collider->left = true;
            entity.position.x = tile.position.x + t_width + e1_width + padding;
            break;
        } case RIGHT: {
            entity.collider->right = true;
            entity.position.x = tile.position.x - t_width - e1_width - padding;
            break;
        }
        case NONE:
            break;
    }
}

bool CollisionSystem::entity_property_updates(Entity &entity, Tile &tile, CollisionSystem::Side side) {
    if (side == NONE)
        return false;

    vec2 normal = {0, 0};

    vec2 dir = normalize(sub(entity.position, tile.position));
    float angle = acos(dot(dir, {1, 0})) * (180.0 / PI);

    if (angle < 45)
        normal = {1, 0};
    else if (angle > 135)
        normal = {-1, 0};
    else if (entity.position.y >= tile.position.y)
        normal = {0, -1};
    else
        normal = { 0, 1};

    entity.physics->velocity = mul(sub(entity.physics->velocity, mul(normal, 2 * dot(normal, entity.physics->velocity))), 0.8);

    if (entity.properties) {
        entity.properties->count--;
    }

    return false;
}

CollisionSystem::Side CollisionSystem::detect_collision(Entity &e1, Entity &e2) {
    float e1_height = abs(e1.texture_size.y * e1.scale.y);
    float e1_width = abs(e1.texture_size.x * e1.scale.x);

    float e2_height = abs(e2.texture_size.y * e2.scale.y);
    float e2_width = abs(e2.texture_size.x * e2.scale.x);

    if (e1.flyable) {
        e1_height *= 0.75;
        e1_width *= 0.9;
    }

    if (e2.flyable) {
        e2_height *= 0.75;
        e2_width *= 0.9;
    }
    // https://stackoverflow.com/questions/29861096/detect-which-side-of-a-rectangle-is-colliding-with-another-rectangle
    float dx = e1.position.x - e2.position.x;
    float dy = e1.position.y - e2.position.y;
    float width = (e1_width + e2_width)/2;
    float height = (e1_height + e2_height)/2;
    float crossWidth = width * dy;
    float crossHeight = height * dx;

    if (abs(dx) <= width && abs(dy) <= height){
        if(crossWidth > crossHeight){
            if (crossWidth > -crossHeight) {
                return Side::BOTTOM;
            } else {
                return Side::RIGHT;
            }
        } else {
            if (crossWidth > -crossHeight || (e2.position.y - (e2_height / 2.f)) < (e1.position.y + (e1_height / 4.f))) {
                return Side::LEFT;
            } else {
                return Side::TOP;
            }
        }
    }
    return Side::NONE;
}

void CollisionSystem::land(Entity &entity) {
    entity.physics->leaving_ice = false;
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
        entity.physics->grounded_friction = 0;
    }
}

void CollisionSystem::set_torches_to_light(int torches_to_light){
    m_torches_to_light = torches_to_light;
}
