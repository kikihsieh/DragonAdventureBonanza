#include "physics_system.hpp"
#include "health_system.hpp"
#include "world.hpp"

#include <cmath>
#include <utility>
#include <scenes/levels/tile_map.hpp>



void HealthSystem::update(float ms) {
    auto entity_it = m_entities->begin();
    while (entity_it != m_entities->end()) {
        if (!entity_it->health || !entity_it->physics) {
            entity_it++;
            continue;
        }

        if (entity_it->health->invincible) {
            entity_it->health->invincible_timer += ms;

            if (entity_it->health->invincible_timer > entity_it->health->invincibility_duration) {
                entity_it->health->invincible = false;
                entity_it->health->invincible_timer = 0;
            }
        }

        if (entity_it->health->is_player && entity_it->physics->grounded) {
            entity_it->health->update_last_safe_timer += ms;
            if (entity_it->health->update_last_safe_timer >= entity_it->health->update_last_safe_frequency) {
                update_last_safe(*entity_it);
                entity_it->health->update_last_safe_timer = 0;
            }
        }

        if (entity_it->physics->off_screen && entity_it->health->is_player) {
            entity_it->health->health -= 1;
            World::playSFX(World::P_DAMAGE);
        }

        if (entity_it->physics->off_screen && entity_it->health->is_player) {
            respawn_at_last_safe(*entity_it);
        }

        if (entity_it->health->health <= 0) {
            if(entity_it->player_tag) {
                m_player_died = true;
            } else if(!entity_it->health->is_boss) {
                entity_it->destroy();
                entity_it = m_entities->erase(entity_it);
                continue;
            }
        }
        entity_it++;
    }
}

bool HealthSystem::init(std::list<Entity> *entities, std::map<int, Tile*>* tiles) {
    m_entities = entities;
    m_tiles = tiles;
    m_player_died = false;
    
    return true;
}



void HealthSystem::update_last_safe (Entity& entity) {

    float e_height = entity.texture_size.y * entity.scale.y;
    float e_width = entity.texture_size.x * entity.scale.x;

    float t_height = TileMap::tile_screen_size.y;
    float t_width = TileMap::tile_screen_size.x;

    std::pair<int, int> tile_pos = TileMap::get_left_top_tile_pos_from_coord(entity.position.x, entity.position.y,
                                                                             {e_width, e_height});

    if (m_tiles->count(TileMap::hash(tile_pos.first, tile_pos.second + ceil(e_height / t_height))) > 0) {
        if (m_tiles->count(TileMap::hash(tile_pos.first - 1, tile_pos.second + ceil(e_height / t_height))) > 0)
            entity.health->last_safe = {entity.position.x - (e_width / 2.f), entity.position.y};
        else if (m_tiles->count(TileMap::hash(tile_pos.first + 1, tile_pos.second + ceil(e_height / t_height))) > 0)
            entity.health->last_safe = {entity.position.x + (e_width / 2.f), entity.position.y};
        else
            entity.health->last_safe = entity.position;
    }

}

void HealthSystem::respawn_at_last_safe(Entity &entity) {
    if (m_player_died)
        return;

    entity.physics->velocity = { 0.f, 0.f };
    entity.physics->off_screen = false;
    entity.position = entity.health->last_safe;
}

bool HealthSystem::player_died() {
    return m_player_died;
}
