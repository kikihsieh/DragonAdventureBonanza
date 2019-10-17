#ifndef DAB_PHYSICS_SYSTEM_HPP
#define DAB_PHYSICS_SYSTEM_HPP

#include <memory>
#include <levels/tile.hpp>
#include <map>
#include <ecs/components/collider.hpp>

class PhysicsSystem {
public:
    void update(float elapsed_ms);

private:
    std::map<int, std::shared_ptr<Tile>> m_tiles;
    std::vector<Collider> m_colliders;
};

#endif //DAB_PHYSICS_SYSTEM_HPP
