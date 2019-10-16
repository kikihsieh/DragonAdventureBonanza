#include "physics_system.hpp"

#include <utility>
#include <levels/tile_map.hpp>

PhysicsSystem::PhysicsSystem(std::map<int, std::shared_ptr<Tile>> tiles) : m_tiles(std::move(tiles)){
}

void PhysicsSystem::update(float elapsed_time) {
    for (auto collider : m_colliders) {
        collider.colliding = Collider::NONE;
    }
}