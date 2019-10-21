#include "physics_system.hpp"
#include "health_system.hpp"

#include <cmath>
#include <utility>
#include <scenes/levels/tile_map.hpp>
#include <ecs/components/health.hpp>

void HealthSystem::update(float ms) {
    for (auto &entity : *m_entities) {
        if (!entity.health) {
            continue;
        }
        
        if (entity.health->health <= 0)
            die(entity);
    }
}

bool HealthSystem::init(std::list<Entity> *entities) {
    m_entities = entities;
    return true;
}


void HealthSystem::die(Entity& entity) {
    //TODO death
}
