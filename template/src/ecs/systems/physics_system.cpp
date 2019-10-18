#include "physics_system.hpp"

#include <utility>

void PhysicsSystem::update(float ms) {
    for (auto &entity : *m_entities) {
        if (!entity.physics) {
            continue;
        }

        entity.physics->velocity.x += entity.physics->acceleration.x;
        entity.physics->velocity.y += entity.physics->acceleration.y;

        float x_step = entity.physics->velocity.x * (ms / 1000);
        float y_step = entity.physics->velocity.y * (ms / 1000);

        entity.position.x += x_step;
        entity.position.y += y_step;
    }
}

bool PhysicsSystem::init(std::vector<Entity> *entities, std::map<int, Tile *> tiles) {
    m_entities = entities;
    m_tiles = std::move(tiles);

    return true;
}
