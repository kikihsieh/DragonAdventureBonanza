#include "collision_system.hpp"

#include <cmath>
#include <utility>
#include <scenes/levels/tile_map.hpp>
#include "iostream"
#include <cstdint>

void CollisionSystem::update(float ms) {
    for (auto &entity : *m_entities) {
        if (!entity.collider) {
            continue;
        }

        collider_reset();

        if (entity.collider && !entity.is_player_proj && !entity.is_enemy_proj) {
            tile_collisions(entity);

            if (entity.collider->left || entity.collider->right) {
                entity.position.x = entity.old_position.x;
            }
            if (entity.collider->top || entity.collider->bottom) {
				
                entity.position.y = entity.old_position.y;
                entity.physics->velocity.y = 0;
            }

            if(entity.player_tag) {
                player_enemy_collision(entity);
                player_projectile_collision(entity);
            }
            if (entity.enemyai) {
                enemy_projectile_collision(entity);
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

    for (int col = tile_pos.first; col <= tile_pos.first + ceil(e_width / t_width); col++) {
        for (int row = tile_pos.second; row <= tile_pos.second + ceil(e_height / t_height); row++) {
            if (!m_tiles.count(TileMap::hash(col, row))) {
                continue;
            }
            Tile* tile = m_tiles.at(TileMap::hash(col, row));
            collide_with_tile(entity, *tile);
        }
    }
}

void CollisionSystem::player_enemy_collision(Entity& player) {
    auto entity_it = m_entities->begin();
    while (entity_it != m_entities->end()) {
        if(entity_it->collider && !entity_it->player_tag && !entity_it->is_player_proj && !entity_it->is_enemy_proj) {
            // TODO: Existing bug: when enemy is inside player, player kills it.
            CollisionSystem::Side side = detect_collision(*entity_it, player);

            if (side == CollisionSystem::BOTTOM) {
                player.physics->velocity.y = -200.f;
                entity_it->destroy();
                entity_it = m_entities->erase(entity_it);
            } else if (side != NONE) {
                ++entity_it;
                // TODO: update some component so that the health can be updated correctly
                //std::cout << "Collision!\n";
            } else {
                ++entity_it;
            }
        } else {
            ++entity_it;
        }
    }
}

void CollisionSystem::player_projectile_collision(Entity& player) {
    auto entity_it = m_entities->begin();
    while (entity_it != m_entities->end()) {
        if(entity_it->collider && !entity_it->player_tag && !entity_it->enemyai && entity_it->is_enemy_proj) {
            CollisionSystem::Side side = detect_collision(*entity_it, player);
            
            if (side == CollisionSystem::TOP || side == CollisionSystem::BOTTOM ||
                side == CollisionSystem::LEFT || side == CollisionSystem::RIGHT) {
                //if projectile hits anyside of player, remove projectile
                entity_it->destroy();
                entity_it = m_entities->erase(entity_it);
                
                // TODO @Austin: update/deplete player health
            }
			else {
				++entity_it;
			}
		}
		else {
			++entity_it;
		}
    }
}

void CollisionSystem::enemy_projectile_collision(Entity& enemy) {
    auto entity_it = m_entities->begin();
    while (entity_it != m_entities->end()) {
        if (entity_it->collider && !entity_it->player_tag && !entity_it->enemyai && entity_it->is_player_proj) {
            CollisionSystem::Side side = detect_collision(*entity_it, enemy);

            if (side == CollisionSystem::TOP || side == CollisionSystem::BOTTOM ||
                side == CollisionSystem::LEFT || side == CollisionSystem::RIGHT) {
                // if projectile hits anyside of enemy, remove projectile
                // TODO: theres a bug when trying to shooting left and hit right

                entity_it->destroy();
                entity_it = m_entities->erase(entity_it);
                
                // TODO @Austin: update/deplete enemy health and remove enemy ai in health system
			}
			else {
				++entity_it;
			}
		}
		else {
			++entity_it;
		}
    }
}

/**
 * This function expects that the first entity is collidable
 * @param e1 : a collid-able entity
 * @param tile : a tile
 */
void CollisionSystem::collide_with_tile(Entity& e1, Tile &tile) {

    switch (detect_collision(e1, tile)) {
        case TOP:
            e1.collider->top = true;
            // TODO: @Austin please move these two if statements out of this function
            if (e1.airdash)
                e1.airdash->can_airdash = true;

            if (e1.physics) {
                e1.physics->jump_count = 0;
            }
            break;
        case BOTTOM:
            e1.collider->bottom = true;
            break;
        case LEFT:
            e1.collider->left = true;
            break;
        case RIGHT:
            e1.collider->right = true;
            break;
        case NONE:
            break;
    }
}

CollisionSystem::Side CollisionSystem::detect_collision(Entity &e1, Entity &e2) {
    float e1_height = e1.drawable->texture->height * e1.scale.x;
    float e1_width = e1.drawable->texture->width * e1.scale.y;

    float e2_height = e2.drawable->texture->height * e2.scale.x;
    float e2_width = e2.drawable->texture->width * e2.scale.y;

    // https://stackoverflow.com/questions/29861096/detect-which-side-of-a-rectangle-is-colliding-with-another-rectangle
    float dx = e1.position.x - e2.position.x;
    float dy = e1.position.y - e2.position.y;
    float width = (e1_width + e2_width)/2;
    float height = (e1_height + e2_height)/2;
    float crossWidth = width*dy;
    float crossHeight = height*dx;

    if (abs(dx) <= width && abs(dy) <= height){
        if(crossWidth > crossHeight){
            if (crossWidth > -crossHeight) {
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

void CollisionSystem::collider_reset() {
    for (auto &e : *m_entities) {
        if (e.collider) {
            e.collider->reset();
        }
    }
}
