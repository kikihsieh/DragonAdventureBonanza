#include "physics_system.hpp"
#include "health_system.hpp"

#include <cmath>
#include <utility>
#include <scenes/levels/tile_map.hpp>
#include <ecs/components/health.hpp>
#include <iostream>

void HealthSystem::update(float ms) {
    int index = 0;

    for (auto &entity : *m_entities) {

        if (!entity.health || !entity.physics) {
            index++;
            continue;
        }

        if (entity.health->is_player && entity.health->invincible) {
            entity.health->invincible_timer += ms;

            if (entity.health->invincible_timer > entity.health->invincibility_duration) {
                entity.health->invincible = false;
                entity.health->invincible_timer = 0;
            }
        }

        if(entity.health->is_player && entity.physics->grounded) {
            entity.health->update_last_safe_timer += ms;
            if (entity.health->update_last_safe_timer >= entity.health->update_last_safe_frequency) {
                update_last_safe(entity);
                entity.health->update_last_safe_timer = 0;
            }
        }

        if (entity.physics->off_screen && entity.health->is_player) {
            entity.health->health -= 1;
        }

        if (entity.health->health <= 0)
            die(entity, index);

        if (entity.physics->off_screen && entity.health->is_player) {
            respawn_at_last_safe(entity);
        }

        index++;
    }
}

bool HealthSystem::init(std::list<Entity> *entities, const std::map<int, Tile*>& tiles) {
    m_entities = entities;
    m_tiles = tiles;
    m_player_died = false;
    return true;
}

void HealthSystem::die(Entity& entity, int index) {
    if (entity.health->is_player)
        m_player_died = true;
    else {
        entity.destroy();
        auto it = m_entities->begin();
        advance(it, index);
        m_entities->erase(it);
    }
}

void HealthSystem::update_last_safe (Entity& entity) {

    float e_height = entity.drawable->texture->height * entity.scale.y;
    float e_width = entity.drawable->texture->width * entity.scale.x;

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

}

void HealthSystem::respawn_at_last_safe(Entity &entity) {
    if (m_player_died)
        return;

    entity.physics->off_screen = false;
    entity.position = entity.health->last_safe;
}

bool HealthSystem::player_died() {
    return m_player_died;
}