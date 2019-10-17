#include "physics_system.hpp"

#include <utility>
#include <levels/tile_map.hpp>

void PhysicsSystem::update(float elapsed_time) {
    for (auto collider : m_colliders) {
        collider.colliding = Collider::NONE;
    }
}