#include "physics_system.hpp"

#include <utility>
#include <levels/tile_map.hpp>

void PhysicsSystem::update(float ms) {
    for (auto &entity : *m_entities) {
        if (!entity.physics) {
            continue;
        }

        float x_step = entity.physics->velocity.x * (ms / 1000);
        float y_step = entity.physics->velocity.y * (ms / 1000);

        if (entity.input) {
            // inputs here
        } else {
            entity.physics->velocity.x += entity.physics->acceleration.x;
            entity.physics->velocity.y += entity.physics->acceleration.y;

            entity.position.x += x_step;
            entity.position.y += y_step;
        }

        if (entity.collider) {
            tile_collisions(entity);
            entity_collisions(entity);
        }
    }
}

bool PhysicsSystem::init(std::vector<Entity> *entities, std::map<int, Tile *> tiles) {
    m_entities = entities;
    m_tiles = std::move(tiles);

    return true;
}

void PhysicsSystem::tile_collisions(Entity& entity) {
    std::pair<int, int> tile_pos = TileMap::get_tile_pos_from_coord(entity.position.x, entity.position.y);
    int col = tile_pos.first;
    int row = tile_pos.second;
}

void PhysicsSystem::entity_collisions(Entity& entity) {
    // TODO: implement collisions between other entities
}
