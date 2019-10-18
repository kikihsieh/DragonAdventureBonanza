#ifndef DAB_PHYSICS_SYSTEM_HPP
#define DAB_PHYSICS_SYSTEM_HPP

#include <ecs/entities/tile.hpp>
#include <map>

class PhysicsSystem {
public:
    bool init(const std::vector<Entity> &entities, std::map<int, Tile*> tiles);

    void update(float ms);

private:
    std::vector<Entity> m_entities;
    std::map<int, Tile*> m_tiles;
};

#endif //DAB_PHYSICS_SYSTEM_HPP
