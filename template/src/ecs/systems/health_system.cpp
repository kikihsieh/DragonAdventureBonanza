#include "physics_system.hpp"
#include "health_system.hpp"

#include <cmath>
#include <utility>
#include <scenes/levels/tile_map.hpp>
#include <ecs/components/health.hpp>
#include <iostream>

void HealthSystem::update(float ms) {
    for (auto &entity : *m_entities) {
        if (!entity.health || !entity.physics) {
            continue;
        }

//        if(entity.health->is_player)
//            std::cout << entity.physics->grounded << std::endl;

        if(entity.health->is_player && entity.physics->grounded) {
            entity.health->update_last_safe_timer += ms;
            if (entity.health->update_last_safe_timer >= entity.health->update_last_safe_frequency) {
                update_last_safe(entity);
                entity.health->update_last_safe_timer = 0;
            }
        }

        if (entity.physics->off_screen) {
            entity.health->health -= 1;
            respawn_at_last_safe(entity);
        }

        if (entity.health->health <= 0)
            die(entity);
    }
}

bool HealthSystem::init(std::list<Entity> *entities, const std::map<int, Tile*>& tiles) {
    m_entities = entities;
    m_tiles = tiles;
    return true;
}


void HealthSystem::die(Entity& entity) {
    //TODO death
}

void HealthSystem::update_last_safe (Entity& entity) {
    float e_height = entity.drawable->texture->height * entity.scale.x;
    float e_width = entity.drawable->texture->width * entity.scale.y;

    float t_height = TileMap::tile_screen_size.y;
    float t_width = TileMap::tile_screen_size.x;

    std::pair<int, int> tile_pos = TileMap::get_tile_pos_from_coord(entity.position.x, entity.position.y, {e_width, e_height});

    if (m_tiles.count(TileMap::hash(tile_pos.first, tile_pos.second + ceil(e_height / t_height))) > 0) {
        if (m_tiles.count(TileMap::hash(tile_pos.first - 1, tile_pos.second + ceil(e_height / t_height))) > 0)
            entity.health->last_safe = {entity.position.x - (e_width / 2.f), entity.position.y};
        else if (m_tiles.count(TileMap::hash(tile_pos.first + 1, tile_pos.second + ceil(e_height / t_height))) > 0)
                entity.health->last_safe = {entity.position.x + (e_width / 2.f), entity.position.y};
        else
            entity.health->last_safe = entity.position;
    }
//    try {
//        Tile *tile = m_tiles.at(TileMap::hash(tile_pos.first, tile_pos.second - 1));
//        entity.health->last_safe = entity.position;
//    } catch(const std::exception& e) {}

}

void HealthSystem::respawn_at_last_safe(Entity &entity) {
    entity.physics->off_screen = false;
    entity.position = entity.health->last_safe;
}
